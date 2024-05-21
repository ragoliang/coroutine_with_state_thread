#include "Coroutine.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

extern int _st_active_count;

void do_some_work(int a)
{
    printf("thread[%d]\n", a);
}

int Coroutine_test()
{
    int a = 1;
    auto lamda_co = [&]() {
        printf("cid=%ld, in lamda_co, time=%ld, a=%d\n", st_thread_self(), time(nullptr), a);
        //while(st_usleep(1 * 1000 * 1000) == 0) {

        //}
        st_usleep(1 * 1000 * 1000);
        printf("sleep done, in cid =%ld, time=%ld\n", st_thread_self(), time(nullptr));
    };

    Coroutine co;
    Coroutine co1(lamda_co);
    Coroutine co2(lamda_co);
    Coroutine co3(lamda_co);
    Coroutine co4(do_some_work, 1);
    Coroutine co5(do_some_work, 2);
    std::cout << "co.cid=" << co.get_cid() << std::endl;
    std::cout << "co1.cid=" << co1.get_cid() << std::endl;
    std::cout << "co2.cid=" << co2.get_cid() << std::endl;
    std::cout << "co3.cid=" << co3.get_cid() << std::endl;
    std::cout << "co4.cid=" << co4.get_cid() << std::endl;
    std::cout << "co5.cid=" << co5.get_cid() << std::endl;

    //st_usleep(3 * 1000 * 1000);
    std::cout << "exit Coroutine_test" << std::endl;
}

int main(int argc, char** argv)
{
   if (st_set_eventsys(ST_EVENTSYS_ALT) < 0) {
        srs_trace("st_set_eventsys failed");
        return -1;
    }

    if (st_init() < 0) {
        srs_trace("st_init failed");
        return -1;
    }
    Coroutine_test();

    printf("wait for all thread completed, _st_active_count=%d\n", _st_active_count);
    printf("cur cid=%ld\n", st_thread_self());
    st_usleep(5 * 1000 * 1000);
    st_thread_exit(NULL);
}
