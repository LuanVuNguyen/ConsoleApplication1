////#define CURL_STATICLIB
////#include "curl/curl.h"
////#include <iostream>
////#include <string>
////#include <thread>
////#include <fstream>
////#include <mutex>
////#include <vector>
////#ifdef _DEBUG
////#pragma comment(lib,"curl/libcurl_a_debug.lib")
////#else
////#pragma comment(lib,"curl/libcurl_a.lib")
////#endif
////
////#pragma comment(lib,"Normaliz.lib")
////#pragma comment(lib,"Ws2_32.lib")
////#pragma comment(lib,"Wldap32.lib")
////#pragma comment(lib,"Crypt32.lib")
////#pragma comment(lib,"Advapi32.lib")
////
//using namespace std;
//
//struct Range {
//    int start;
//    int end;
//};
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
//    cout << shared_data->data.size() << endl;
//    return bytes_written;
//}
//
//static void download_range(Range range, const char* url, SharedData* shared_data) {
//    CURL* curl = curl_easy_init();
//  
//    if (curl) {
//        
//        curl_easy_setopt(curl, CURLOPT_URL, url);
//
//        char range_header[50];
//        snprintf(range_header, sizeof(range_header), "%d-%d", range.start, range.end);
//        curl_easy_setopt(curl, CURLOPT_RANGE, range_header);
//
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
//        cout << shared_data << endl;
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, shared_data);
//        
//        CURLcode res = curl_easy_perform(curl);
//
//        if (res != CURLE_OK) {
//            cerr << "Error downloading range " << range.start << "-" << range.end << ": " << curl_easy_strerror(res) << endl;
//        }
//
//        curl_easy_cleanup(curl);
//    }
//}
//
//int main() {
//    const char* url = "https://cdn.fbsbx.com/v/t59.2708-21/270698363_2085881624904828_5544319239191867266_n.pdf/nhom6_ca4_bai5_TH_CHTTT.pdf?_nc_cat=111&ccb=1-7&_nc_sid=0cab14&_nc_ohc=1zd-QnAruNcAX8FtB1k&_nc_oc=AQnn1vS_bYqBp7tZbz7FnX1hOgX5DKiCaQDHbX-9MoydlU8x-nWkEsdPFyjfBESGuLA9ebdcNJGSfKVTL-4NE5mo&_nc_ht=cdn.fbsbx.com&oh=03_AdR_pL_NTlpO-QtVKXVRu9UcF3D7T_OBfPFbNh2kt80abA&oe=64329845&dl=1";
//    const int num_threads = 3;
//
//    CURLcode res = curl_global_init(CURL_GLOBAL_DEFAULT);
//    if (res != CURLE_OK) {
//        cerr << "Error initializing curl: " << curl_easy_strerror(res) << endl;
//        return 1;
//    }
//
//    CURL* curl = curl_easy_init();
//    if (curl) {
//        curl_easy_setopt(curl, CURLOPT_URL, url);
//
//        double content_length;
//        curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
//        curl_easy_perform(curl);
//        curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &content_length);
//        curl_easy_setopt(curl, CURLOPT_NOBODY, 0);
//        int part_size = static_cast<int>(content_length / num_threads);
//        int content_length_int = static_cast<int>(content_length);
//        int remainder = content_length_int % num_threads;
//
//        // Initialize shared data
//        SharedData shared_data;
//
//        thread threads[num_threads];
//
//        for (int i = 0; i < num_threads; i++) {
//            Range range = {
//                i * part_size,
//                (i + 1) * part_size - 1
//            };
//
//            if (i == num_threads - 1) {
//                range.end += remainder;
//            }
//
//            // Pass a pointer to the shared data to each thread
//            threads[i] = thread(download_range, range, url, &shared_data);
//            
//        }
//        
//        for (int i = 0; i < num_threads; i++) {
//            threads[i].join();
//        }
//        // The shared data now contains the downloaded file
//        ofstream file("downloaded_file.txt", ios::binary);
//        
//        file.write(&shared_data.data[0], shared_data.data.size());
//    }
//    curl_global_cleanup();
//    return 0;
//}