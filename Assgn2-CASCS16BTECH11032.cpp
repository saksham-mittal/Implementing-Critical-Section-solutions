// This code belongs to Saksham Mittal
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <fstream>
#include <atomic>

using namespace std;
int N, k, csSeed, remSeed, randCSTime, randRemTime;

double *waitingTime, averageWaitingTime = 0;

atomic<int> lock1(0);
FILE * fp;

void testCS(int n) {
    // thread::id this_id = this_thread::get_id();
    int this_id = n + 1;

    // cout << "Thread " << n + 1 << " has id " << this_id << endl;

    for(int i=0; i<k; i++) {
        // each thread will enter CS k times
        time_t now = time(0);
        tm *ltm = localtime(&now);
        fprintf(fp, "%dth CS request by Thread %d at %d:%d\n", i + 1, this_id, ltm->tm_min, ltm->tm_sec);
        waitingTime[this_id - 1] += (-now);

        int x = 0;
        while(!atomic_compare_exchange_weak(&lock1, &x, 1)) {
            x = 0;
        }     // do nothing means nothing

        now = time(0);
        ltm = localtime(&now);
        fprintf(fp, "%dth CS entry by Thread %d at %d:%d\n", i + 1, this_id, ltm->tm_min, ltm->tm_sec);
        waitingTime[this_id - 1] += (now);

        srand(csSeed);
        randCSTime = rand()%10 + 1;    // get random CS Time
        this_thread::sleep_for(chrono::milliseconds(randCSTime));      // simulate a thread executing in CS

        now = time(0);
        ltm = localtime(&now);
        fprintf(fp, "%dth CS exit by Thread %d at %d:%d\n", i + 1, this_id, ltm->tm_min, ltm->tm_sec);

        lock1 = 0;

        srand(remSeed);
        randRemTime = rand()%10 + 1;    // get random Remainder Section Time
        this_thread::sleep_for(chrono::milliseconds(randRemTime));     // simulate a thread executing in CS

    }
}

int main(int argc, char const *argv[]) {
    ifstream infile("inp-params.txt");
    infile >> N >> k >> csSeed >> remSeed;
    thread threads[N];

    waitingTime = new double[N];

    fp = fopen ("CAS-Log.txt", "w+");

    for (int i=0; i<N; i++) {
        threads[i] = thread(testCS, i);
    }

    for (int i=0; i<N; i++) {
        threads[i].join();
    }

    fclose(fp);

    for(int i=0; i<N; i++)      averageWaitingTime += waitingTime[i];
    averageWaitingTime /= (double)N;

    ofstream avgTimes;
    avgTimes.open("Average_time.txt", ios::app);
    avgTimes << "CAS Algorithm: " << endl;
    avgTimes << averageWaitingTime << " seconds" << endl;
    avgTimes.close();

  return 0;
}
