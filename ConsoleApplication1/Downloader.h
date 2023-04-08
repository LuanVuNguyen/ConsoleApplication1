#ifndef __Downloader__Downloader__
#define __Downloader__Downloader__

#include "Common.h"


typedef function<void(int)> DownloaderCallback;

class Downloader
{
public:
    static Downloader* instance();
    virtual ~Downloader();

    /**
     Setup a callback function. When all tasks are done, call it.
     */
    void setCompletedCallback(DownloaderCallback callback);

    /**
     Download a file from url.
     @return: task ID. If failed, return -1
     */
    int download(string url, string folder);
    int download(string url, string folder, DownloaderCallback callback);
    int download(string url, string folder, string filename);
    int download(string url, string folder, string filename, DownloaderCallback callback);

protected:
    /**
     Description of a download task
     */
    struct Task
    {
        int id;
        string url;
        string folder;
        string filename;
        DownloaderCallback callback;

        Task() : id(0) {}
    };

private:
    Downloader(); // for singleton
    static void* runNextTask(void*); // for thread start
    void runNextTask(); // for download the next task in the waiting list
    void callCallbackSafely(DownloaderCallback callback, int); // make sure the callbacks are executed one by one

private:
    int m_lastId;

    queue<Task> m_waiting;
    static pthread_mutex_t s_waiting;

    unordered_map<int, pthread_t> m_running;
    static pthread_mutex_t s_running;

    int m_threadCount;
    static pthread_mutex_t s_threadCount;

    DownloaderCallback m_onCompleted;
    static pthread_mutex_t s_callback;

};

#endif /* defined(__Downloader__Downloader__) */

