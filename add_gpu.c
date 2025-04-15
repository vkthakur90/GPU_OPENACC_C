#include <stdio.h>

#ifndef MAX_DATA
#define MAX_DATA 100000000
#endif

#ifndef BATCH_DATA
#define BATCH_DATA 1000000
#endif

struct ProgramData 
{ 
    size_t size;
    float num1[MAX_DATA];
    float num2[MAX_DATA];
    float res[MAX_DATA];
};

struct BatchData 
{ 
    size_t size;
    float num1[BATCH_DATA];
    float num2[BATCH_DATA];
    float sum[BATCH_DATA];
    float diff[BATCH_DATA];
    float res[BATCH_DATA];
};

static struct ProgramData data;
static struct BatchData batch;

void ProgramData_init(struct ProgramData * restrict data_ptr) 
{
    data_ptr->size = MAX_DATA;
    for (size_t idx = 0; idx < data_ptr->size; ++idx) 
    {
        data_ptr->num1[idx] = (float)((idx + 1) * 3);
        data_ptr->num2[idx] = (float)((idx + 1) * 2);
    }
}

void BatchData_compute(struct BatchData * restrict batch_ptr) 
{
    #pragma acc parallel loop default(present)
    for (size_t idx = 0; idx < batch_ptr->size; ++idx) 
    {
        batch_ptr->sum[idx]  = batch_ptr->num1[idx] + batch_ptr->num2[idx];
        batch_ptr->diff[idx] = batch_ptr->num1[idx] - batch_ptr->num2[idx];
        batch_ptr->res[idx]  = batch_ptr->sum[idx]  * batch_ptr->diff[idx];
    }
}

int main() 
{
    size_t current_size;

    ProgramData_init(&data);
    
    for(size_t start = 0; start < MAX_DATA; start += BATCH_DATA)
    {
        current_size = (start + BATCH_DATA < MAX_DATA) ? BATCH_DATA : MAX_DATA - start;
        batch.size = current_size;
        
        for(size_t idx = 0; idx < batch.size; ++idx)
        {
            batch.num1[idx] = data.num1[start + idx];
            batch.num2[idx] = data.num2[start + idx];
        }
        
        #pragma acc data copy(data)
        {
            ProgramData_compute(&data);
        }
        
        for(size_t idx = 0; idx < batch.size; ++idx)
        {
            data.res[start + idx] = batch.res[idx];
        }
    }
    
    for (size_t idx = 0; idx < 10; ++idx) 
    {
        printf("%f\n", data.res[idx]);
    }

    return 0;
}
