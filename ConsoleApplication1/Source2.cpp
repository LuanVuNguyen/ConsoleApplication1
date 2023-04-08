//#define CURL_STATICLIB
//#include "curl/curl.h"
//#include <iostream>
//#include <string>
//#include <thread>
//#include <fstream>
//#include <mutex>
//#include <vector>
//#include <stdio.h>
//#include <sstream>
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
//
//// Global variables for synchronization
//mutex mtx;
//vector<char> buffer;
//
//// Function to be executed by each thread
//void downloadThread(const char* url, long start, long end) {
//    CURL* curl = curl_easy_init();
//    if (curl) {
//        stringstream range;
//        range << start << "-" << end;
//        if (!range.str().empty()) {
//            curl_easy_setopt(curl, CURLOPT_URL, url);
//            curl_easy_setopt(curl, CURLOPT_RANGE, range.str().c_str());
//
//            // Write callback function for libcurl
//            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](void* ptr, size_t size, size_t nmemb, void* stream) {
//                mtx.lock();
//                char* data = static_cast<char*>(ptr);
//                buffer.insert(buffer.end(), data, data + size * nmemb);
//                mtx.unlock();
//                return size * nmemb;
//                });
//
//            CURLcode res = curl_easy_perform(curl);
//            if (res != CURLE_OK) {
//                cerr << "Error downloading " << url << endl;
//            }
//            curl_easy_cleanup(curl);
//        }
//    }
//}
//
//int main() {
//    const char* url = "https://cdn.fbsbx.com/v/t59.2708-21/329402164_547894143963869_5199911669329303631_n.pdf/JAVA2023_DeTai-XayDungMangXaHoi_Ngay4_2.pdf?_nc_cat=108&ccb=1-7&_nc_sid=0cab14&_nc_ohc=B3hyUZL0DCsAX9Zbfb1&_nc_ht=cdn.fbsbx.com&oh=03_AdRR93Ekq6gdTpW5pVJA_dyeST7YMH-TJQ2Up3dhPkrvyA&oe=64335F77&dl=1";
//    const char* filename = "file.pdf";
//    const int numThreads = 4;
//
//    CURL* curl = curl_easy_init();
//    if (curl) {
//        curl_easy_setopt(curl, CURLOPT_URL, url);
//        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
//        CURLcode res = curl_easy_perform(curl);
//        if (res == CURLE_OK) {
//            double contentLength;
//            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &contentLength);
//            if (res == CURLE_OK) {
//                vector<thread> threads;
//                long chunkSize = contentLength / numThreads;
//                for (int i = 0; i < numThreads; i++) {
//                    long start = i * chunkSize;
//                    long end = start + chunkSize - 1;
//                    if (i == numThreads - 1) {
//                        end = contentLength - 1;
//                    }
//                    threads.emplace_back(downloadThread, url, start, end);
//                }
//                for (auto& t : threads) {
//                    t.join();
//                }
//                ofstream outFile(filename, ios::out | ios::binary);
//                if (outFile.is_open()) {
//                    outFile.write(&buffer[0], buffer.size());
//                    outFile.close();
//                    cout << "File downloaded successfully." << endl;
//                }
//                else {
//                    cerr << "Error writing to file." << endl;
//                }
//            }
//            else {
//                cerr << "Error getting content length." << endl;
//            }
//        }
//        else {
//            cerr << "Error checking file existence." << endl;
//        }
//        curl_easy_cleanup(curl);
//    }
//    else {
//        cerr << "Error initializing curl." << endl;
//    }
//    return 0;
//}