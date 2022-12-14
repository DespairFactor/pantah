// SPDX-License-Identifier: GPL-2.0-only
/* init.c
 *
 * Android Vendor Hook Support
 *
 * Copyright 2021 Google LLC
 */

#include <linux/module.h>
#include <trace/hooks/cgroup.h>
#include <trace/hooks/sched.h>

extern void rvh_cgroup_force_kthread_migration_pixel_mod(void *data, struct task_struct *tsk,
							 struct cgroup *dst_cgrp,
							 bool *force_migration);
extern void vh_rebuild_root_domains_bypass_pixel_mod(void *data, bool tasks_frozen, bool *bypass);

static int vh_cgroup_init(void)
{
	int ret;

	ret = register_trace_android_rvh_cgroup_force_kthread_migration(
		rvh_cgroup_force_kthread_migration_pixel_mod, NULL);
	if (ret)
		return ret;

	ret = register_trace_android_vh_rebuild_root_domains_bypass(
		vh_rebuild_root_domains_bypass_pixel_mod, NULL);
	if (ret)
		return ret;

	return 0;
}

module_init(vh_cgroup_init);
MODULE_LICENSE("GPL v2");
