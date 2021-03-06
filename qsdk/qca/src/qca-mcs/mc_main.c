/*
 * Copyright (c) 2012, 2015, 2017 The Linux Foundation. All rights reserved.
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include "mc_netfilter.h"
#include "mc_netlink.h"
#include "mc_snooping.h"
#include "mc_forward.h"

static int __init mc_init(void)
{
	if (mc_netlink_init())
		goto err0;

	if (mc_netfilter_init())
		goto err1;

	mc_snooping_init();

	printk("QCA multicast snooping installed successfully\n");
	return 0;

err1:
	mc_netlink_exit();
err0:
	printk("QCA multicast snooping failed to install\n");
	return -1;
}

static void __exit mc_exit(void)
{
	mc_netlink_exit();
	mc_netfilter_exit();
	mc_snooping_exit();

	printk("QCA multicast snooping uninstalled\n");
}


module_init(mc_init);
module_exit(mc_exit);
MODULE_LICENSE("GPL v2");

