#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
// 交替打印0和1 C语言版本
pthread_mutex_t m_lock ;
pthread_cond_t cond ;
int which = 0;
void* print1() {
    printf("print1\n");
    while (1) {
        pthread_mutex_lock(&m_lock);
        while (which != 1) {
            // printf("print1 wait\n");
            pthread_cond_wait(&cond, &m_lock);
        }
        printf("pid: %d 1\n", (int)pthread_self());
        which = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&m_lock);
        sleep(1);
    }
}
void* print0() {
        printf("print0\n");
        while (1) {
            pthread_mutex_lock(&m_lock);
            while (which != 0) {
                // printf("print0 wait\n");
                pthread_cond_wait(&cond, &m_lock);
            }
            printf("pid: %d 0\n", (int)pthread_self());
            which = 1;
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&m_lock);
            sleep(1);
        }
  
}

int main() {
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&m_lock, NULL);
    pthread_t t1, t2;
    printf("main\n");

    pthread_create(&t1, NULL, print0, NULL);
    pthread_create(&t2, NULL, print1, NULL);

    pthread_join(t2, NULL);
    pthread_join(t1, NULL);

}