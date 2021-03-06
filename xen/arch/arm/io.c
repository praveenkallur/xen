/*
 * xen/arch/arm/io.c
 *
 * ARM I/O handlers
 *
 * Copyright (c) 2011 Citrix Systems.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <xen/config.h>
#include <xen/lib.h>
#include <xen/spinlock.h>
#include <xen/sched.h>
#include <asm/current.h>
#include <asm/mmio.h>

int handle_mmio(mmio_info_t *info)
{
    struct vcpu *v = current;
    int i;
    const struct mmio_handler *handler = NULL;
    const struct vmmio *vmmio = &v->domain->arch.vmmio;

    for ( i = 0; i < vmmio->num_entries; i++ )
    {
        handler = &vmmio->handlers[i];

        if ( (info->gpa >= handler->addr) &&
             (info->gpa < (handler->addr + handler->size)) )
            break;
    }

    if ( i == vmmio->num_entries )
        return 0;

    if ( info->dabt.write )
        return handler->ops->write(v, info, handler->priv);
    else
        return handler->ops->read(v, info, handler->priv);
}

void register_mmio_handler(struct domain *d,
                           const struct mmio_handler_ops *ops,
                           paddr_t addr, paddr_t size, void *priv)
{
    struct vmmio *vmmio = &d->arch.vmmio;
    struct mmio_handler *handler;

    BUG_ON(vmmio->num_entries >= MAX_IO_HANDLER);

    spin_lock(&vmmio->lock);

    handler = &vmmio->handlers[vmmio->num_entries];

    handler->ops = ops;
    handler->addr = addr;
    handler->size = size;
    handler->priv = priv;

    /*
     * handle_mmio is not using the lock to avoid contention.
     * Make sure the other processors see the new handler before
     * updating the number of entries
     */
    dsb(ish);

    vmmio->num_entries++;

    spin_unlock(&vmmio->lock);
}

int domain_io_init(struct domain *d)
{
   spin_lock_init(&d->arch.vmmio.lock);
   d->arch.vmmio.num_entries = 0;

   return 0;
}

/*
 * Local variables:
 * mode: C
 * c-file-style: "BSD"
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
