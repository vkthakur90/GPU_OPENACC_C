#include <stdio.h>
#include <stddef.h>

#ifndef MAX_DATA
#define MAX_DATA 1000000
#endif

struct ProgramData 
{ 
    size_t size;
    struct {
        float num1[MAX_DATA];
        float num2[MAX_DATA];
    } inputs;
    struct {
        float sum[MAX_DATA];
        float diff[MAX_DATA];
        float prod[MAX_DATA];
        float ratio[MAX_DATA];
    } outputs;
};

static struct ProgramData data;

void ProgramData_init(struct ProgramData * restrict data_ptr) 
{
    #pragma acc parallel loop default(present)
    for (size_t idx = 0; idx < data_ptr->size; ++idx) 
    {
        data_ptr->inputs.num1[idx] = (float)((idx + 1) * 3);
        data_ptr->inputs.num2[idx] = (float)((idx + 1) * 2);
    }
}

void ProgramData_compute(struct ProgramData * restrict data_ptr) 
{
    #pragma acc parallel loop default(present)
    for (size_t idx = 0; idx < data_ptr->size; ++idx) 
    {
        float a = data_ptr->inputs.num1[idx];
        float b = data_ptr->inputs.num2[idx];

        data_ptr->outputs.sum[idx]   = a + b;
        data_ptr->outputs.diff[idx]  = a - b;
        data_ptr->outputs.prod[idx]  = a * b;
        data_ptr->outputs.ratio[idx] = (b != 0.0f) ? (a / b) : 0.0f;
    }
}

int main() 
{
    data.size = MAX_DATA;

    #pragma acc data copy(data)
    {
        ProgramData_init(&data);
        ProgramData_compute(&data);
    }

    for (size_t idx = 0; idx < 10; ++idx) 
    {
        printf("%f\t%f\t%f\t%f\n", 
            data.outputs.sum[idx], 
            data.outputs.diff[idx],
            data.outputs.prod[idx],
            data.outputs.ratio[idx]
        );
    }

    return 0;
}
