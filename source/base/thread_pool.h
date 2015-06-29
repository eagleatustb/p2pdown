#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include "third_party/chromium/base/threading/sequenced_worker_pool.h"

namespace base
{
class SequencedTaskRunner;
}

// 线程池
namespace michaeltan
{

class ThreadPool
{
public:
    static bool Init();
    static void StopAllThread();

    static bool RunsTasksOnCurrentThread();
    // Returns a unique token that can be used to sequence tasks posted to
    // PostSequencedWorkerTask(). Valid tokens are always nonzero.
    static base::SequencedWorkerPool::SequenceToken GetSequenceToken();

    // Returns the sequence token associated with the given name. Calling this
    // function multiple times with the same string will always produce the
    // same sequence token. If the name has not been used before, a new token
    // will be created.
    static base::SequencedWorkerPool::SequenceToken GetNamedSequenceToken(
        const std::string& name);

    // Returns a SequencedTaskRunner wrapper which posts to this
    // SequencedWorkerPool using the given sequence token. Tasks with nonzero
    // delay are posted with SKIP_ON_SHUTDOWN behavior and tasks with zero delay
    // are posted with BLOCK_SHUTDOWN behavior.
    static scoped_refptr<base::SequencedTaskRunner> GetSequencedTaskRunner(
        base::SequencedWorkerPool::SequenceToken token);

    static scoped_refptr<base::SequencedTaskRunner> GetNamedSequenceTaskRunner(
        const std::string& name);

    static scoped_refptr<base::SequencedTaskRunner> GetUniqueSequenceTaskRunner();

    static bool PostTask(const tracked_objects::Location& from_here, 
                         const base::Closure& task);

    static bool PostDelayedTask(const tracked_objects::Location& from_here,
                                const base::Closure& task,
                                base::TimeDelta delay);

    // Like PostWorkerTask above, but provides sequencing semantics. This means
    // that tasks posted with the same sequence token (see GetSequenceToken())
    // are guaranteed to execute in order. This is useful in cases where you're
    // doing operations that may depend on previous ones, like appending to a
    // file.
    //
    // The task will be guaranteed to run to completion before shutdown
    // (BLOCK_SHUTDOWN semantics).
    //
    // Returns true if the task was posted successfully. This may fail during
    // shutdown regardless of the specified ShutdownBehavior.
    static bool PostSequencedWorkerTask(
        base::SequencedWorkerPool::SequenceToken sequence_token,
        const tracked_objects::Location& from_here,
        const base::Closure& task);

    // Like PostSequencedWorkerTask above, but allows you to specify a named
    // token, which saves an extra call to GetNamedSequenceToken.
    static bool PostNamedSequencedWorkerTask(
        const std::string& token_name,
        const tracked_objects::Location& from_here,
        const base::Closure& task);

    static bool PostDelayedSequencedWorkerTask(
        base::SequencedWorkerPool::SequenceToken sequence_token,
        const tracked_objects::Location& from_here,
        const base::Closure& task,
        base::TimeDelta delay);

    static void FinalizeToken(base::SequencedWorkerPool::SequenceToken token);
    static void FinalizeNamedToken(const std::string& name);
    
private:
    static base::SequencedWorkerPool* sequencedWorkerPool_;
};
}

#endif  // _SE_TRANSLATED_THREAD_H_
