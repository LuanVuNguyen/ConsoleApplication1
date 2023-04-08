//#define CURL_STATICLIB
//#define _CRT_SECURE_NO_WANINGS
//#include "curl/curl.h"
//#include <iostream>
//#include <string>
//#include <thread>
//#include <fstream>
//#include <mutex>
//#include <vector>
//#include <stdio.h>
//#include <stdlib.h>
//
//
//#ifdef _DEBUG
//#pragma comment(lib,"curl/libcurl_a_debug.lib")
//#else
//#pragma comment(lib,"curl/libcurl_a.lib")
//#endif
//
//#pragma comment(lib,"Normaliz.lib")
//#pragma comment(lib,"Ws2_32.lib")
//#pragma comment(lib,"Wldap32.lib")
//#pragma comment(lib,"Crypt32.lib")
//#pragma comment(lib,"Advapi32.lib")
//
//using namespace std;
//std::mutex file_mutex;
//
//struct SharedData {
//    vector<char> data;
//    mutex mtx;
//};
//
//static size_t write_callback(void* buffer, size_t size, size_t nmemb, void* userp) {
//    // Get the shared data from userp
//    SharedData* shared_data = reinterpret_cast<SharedData*>(userp);
//
//    // Lock the mutex to prevent concurrent access to the shared data
//    lock_guard<mutex> lock(shared_data->mtx);
//
//    // Write to the shared data vector
//    size_t bytes_written = size * nmemb;
//    char* buffer_ptr = reinterpret_cast<char*>(buffer);
//    shared_data->data.insert(shared_data->data.end(), buffer_ptr, buffer_ptr + bytes_written);   
//    cout << shared_data->data[0] << endl;
//    return bytes_written;
//}
//
//void download_file_range(const string& url, const string& filename, int range_start, int range_end, int thread_id) {
//    CURL* curl;
//    FILE* fp;
//    CURLcode res;
//    string new_filename =  "file_" + to_string(thread_id)+".txt";
//    
//    curl = curl_easy_init();
//    if (curl) {
//        if (fopen_s(&fp, filename.c_str(), "wb") == 0) {
//            std::unique_lock<std::mutex> lock(file_mutex); // lock file access    
//            SharedData shared_data;
//            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//            curl_easy_setopt(curl, CURLOPT_RANGE, to_string(range_start) + "-" + to_string(range_end));
//            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
//            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &shared_data);
//            res = curl_easy_perform(curl);
//            curl_easy_cleanup(curl);
//            fclose(fp);
//            lock.unlock(); // unlock file access
//            if (res == CURLE_OK) {
//                cout << "File downloaded successfully." << endl;
//            }
//            else {
//                cout << "Failed to download file." << endl;
//            }
//        }
//        else {
//            std::cout << "Failed to open file." << std::endl;
//        }
//    }
//}
//
//void calculate_range(const string& url, int file_size, int num_threads, int thread_id, int& range_start, int& range_end) {
//    int chunk_size = file_size / num_threads;
//    int last_chunk_size = file_size - (num_threads - 1) * chunk_size;
//
//    if (thread_id == num_threads - 1) {
//        range_start = thread_id * chunk_size;
//        range_end = range_start + last_chunk_size - 1;
//    }
//    else {
//        range_start = thread_id * chunk_size;
//        range_end = range_start + chunk_size - 1;
//    }
//}
//
//int main() {
//    const string url = "https://i.pinimg.com/564x/d6/cc/f4/d6ccf43a8b34b7766075f9c12fcf473e.jpg";
//    const string filename = "file.jpg";
//    const int num_threads = 3;
//
//    CURL* curl;
//    curl = curl_easy_init();
//    if (curl) {
//        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//        curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
//        curl_easy_setopt(curl, CURLOPT_HEADER, 1);
//        curl_easy_perform(curl);
//
//        double file_size;
//        curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &file_size);
//        curl_easy_cleanup(curl);
//
//        vector<thread> threads(num_threads);
//        int range_start, range_end;
//        
//        for (int i = 0; i < num_threads; i++) {
//            calculate_range(url, (int)file_size, num_threads, i, range_start, range_end);
//            Sleep(1000);
//            threads[i] = thread(download_file_range, url,  filename, range_start, range_end,i);
//        }
//
//        for (auto& t : threads) {
//            t.join();
//        }
//
//        //ofstream file("downloaded_file.txt", ios::binary);
//        //
//        //file.write(&shared_data.data[0], shared_data.data.size());
//    }
//
//    return 0;
//}
//
