#ifndef _FG_H_
#define _FG_H_

#include <linux/cred.h>
#include "../../../fs/proc/healthinfo/fg_uid/fg_uid.h"

#ifdef CONFIG_FG_TASK_UID
static inline int current_is_fg(void)
{
	int cur_uid;
	cur_uid = current_uid().val;
	if (is_fg(cur_uid))
		return 1;
	return 0;
}

static inline int task_is_fg(struct task_struct *tsk)
{
	int cur_uid;
	const struct cred *tcred;

	rcu_read_lock();
	tcred = __task_cred(tsk);
	if (!tcred) {
		rcu_read_unlock();
		return 0;
	}
	cur_uid = __kuid_val(tcred->uid);
	rcu_read_unlock();
	if (is_fg(cur_uid))
		return 1;
	return 0;
}
#else
static inline int current_is_fg(void)
{
	return 0;
}

static inline int task_is_fg(struct task_struct *tsk)
{
	return 0;
}

static inline bool is_fg(int uid)
{
	return false;
}
#endif
#endif /*_FG_H_*/
