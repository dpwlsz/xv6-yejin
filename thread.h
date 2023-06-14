// Thread library definition
int thread_create(void (*function) (void *, void *), void *arg1, void *arg2);
int thread_join(int tid);