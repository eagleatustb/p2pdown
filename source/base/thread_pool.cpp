#include "base/thread_pool.h"
#include "third_party/chromium/base/sequenced_task_runner.h"

using base::SequencedWorkerPool;
using base::SequencedTaskRunner;

namespace michaeltan
{
namespace
{
static const int MaxWorkerCount = 32;
SequencedWorkerPool* CreateSequencedWorkerPool()
{
    return new SequencedWorkerPool(MaxWorkerCount, "kugou_"); 
}
}

base::SequencedWorkerPool* ThreadPool::sequencedWorkerPool_ = nullptr;

bool ThreadPool::Init()
{
    if (!sequencedWorkerPool_)
    {
        sequencedWorkerPool_ = CreateSequencedWorkerPool();
        sequencedWorkerPool_->AddRef();
    }
    return true;
}

void ThreadPool::StopAllThread()
{
    if (sequencedWorkerPool_)
    {
        sequencedWorkerPool_->Shutdown();
        sequencedWorkerPool_->Release();
        sequencedWorkerPool_ = NULL;
    }
}

bool ThreadPool::PostTask(const tracked_objects::Location& from_here,
                          const base::Closure& task)
{
    assert(sequencedWorkerPool_);
    bool result = false;
    if (sequencedWorkerPool_)
        result = sequencedWorkerPool_->PostWorkerTask(from_here, task);

    return result;
}

SequencedWorkerPool::SequenceToken ThreadPool::GetSequenceToken()
{
    assert(sequencedWorkerPool_);
    if (sequencedWorkerPool_)
        return sequencedWorkerPool_->GetSequenceToken();
    else
        return SequencedWorkerPool::SequenceToken();
}

SequencedWorkerPool::SequenceToken ThreadPool::GetNamedSequenceToken(
    const std::string& name)
{
    assert(sequencedWorkerPool_);
    if (sequencedWorkerPool_)
        return sequencedWorkerPool_->GetNamedSequenceToken(name);
    else
        return SequencedWorkerPool::SequenceToken();
}

scoped_refptr<SequencedTaskRunner> ThreadPool::GetSequencedTaskRunner( 
    SequencedWorkerPool::SequenceToken token)
{
    assert(sequencedWorkerPool_);
    if (sequencedWorkerPool_)
        return sequencedWorkerPool_->GetSequencedTaskRunner(token);
    else
        return nullptr;
}

scoped_refptr<SequencedTaskRunner> ThreadPool::GetNamedSequenceTaskRunner(
    const std::string& name)
{
    assert(sequencedWorkerPool_);
    if (sequencedWorkerPool_)
    {
        auto token = sequencedWorkerPool_->GetNamedSequenceToken(name);
        return sequencedWorkerPool_->GetSequencedTaskRunner(token);
    }
    else
    {
        return nullptr;
    }   
}

bool ThreadPool::PostSequencedWorkerTask(
    SequencedWorkerPool::SequenceToken sequence_token, 
    const tracked_objects::Location& from_here, const base::Closure& task)
{
    assert(sequencedWorkerPool_);
    bool result = false;
    if (sequencedWorkerPool_)
    {
        result = sequencedWorkerPool_->PostSequencedWorkerTask(
            sequence_token, from_here, task);
    }
    return result;
}

bool ThreadPool::PostNamedSequencedWorkerTask( 
    const std::string& token_name, const tracked_objects::Location& from_here,
    const base::Closure& task )
{
    assert(sequencedWorkerPool_);
    bool result = false;
    if (sequencedWorkerPool_)
    {
        result = sequencedWorkerPool_->PostNamedSequencedWorkerTask(
            token_name, from_here, task);
    }
    return result;
}

bool ThreadPool::PostDelayedTask(const tracked_objects::Location& from_here,
                                 const base::Closure& task, base::TimeDelta delay)
{
    assert(sequencedWorkerPool_);
    bool result = false;
    if (sequencedWorkerPool_)
        result = sequencedWorkerPool_->PostDelayedTask(from_here, task, delay);

    return result;
}

bool ThreadPool::PostDelayedSequencedWorkerTask(
    base::SequencedWorkerPool::SequenceToken sequence_token, 
    const tracked_objects::Location& from_here, const base::Closure& task, 
    base::TimeDelta delay)
{
    assert(sequencedWorkerPool_);
    bool result = false;
    if (sequencedWorkerPool_)
        result = sequencedWorkerPool_->PostDelayedSequencedWorkerTask(
            sequence_token, from_here, task, delay);

    return result;
}

bool ThreadPool::RunsTasksOnCurrentThread()
{
    assert(sequencedWorkerPool_);
    bool result = false;
    if (sequencedWorkerPool_)
        result = sequencedWorkerPool_->RunsTasksOnCurrentThread();

    return result;
}

void ThreadPool::FinalizeToken(base::SequencedWorkerPool::SequenceToken token)
{
    assert(sequencedWorkerPool_);
    if (sequencedWorkerPool_)
        sequencedWorkerPool_->FinalizeToken(token);
}

void ThreadPool::FinalizeNamedToken(const std::string& name)
{
    assert(sequencedWorkerPool_);
    if (sequencedWorkerPool_)
        sequencedWorkerPool_->FinalizeNamedToken(name);
}

scoped_refptr<base::SequencedTaskRunner> ThreadPool::GetUniqueSequenceTaskRunner()
{
    assert(sequencedWorkerPool_);
    if (sequencedWorkerPool_)
    {
        auto token = sequencedWorkerPool_->GetSequenceToken();
        return sequencedWorkerPool_->GetSequencedTaskRunner(token);
    }
    else
    {
        return nullptr;
    }
}

}