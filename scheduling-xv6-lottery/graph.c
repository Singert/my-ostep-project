#include "types.h"
#include "fcntl.h"
#include "user.h"
#include "pstat.h"

// We are going to use this to processes our two processes and
// record their number of ticks every now and then

const int SAMPLE_PERIOD = 75;
const int SAMPLE_WINDOW = 2000;
const int GRAPH_PRIORITY = 1000;
const char*const OUTPUT_FILE = "graph.csv";
int main(int argc, char** argv)
{
    settickets(GRAPH_PRIORITY);
    const int PROCESS_QUANTITY = argc - 1; //to see how many processes we're observing
    int processes[PROCESS_QUANTITY];
    for(int i=0;i<PROCESS_QUANTITY;i++)
        processes[i] = atoi(argv[i+1]);

    struct pstat pinfo = {0};
    if(0>getpinfo(&pinfo))
    {
        fprintf(stderr, "getpinfo() failed\n")
        exit();
    }
    int fp = stdout;

    fprintf(fp, "time, ");
    for(int i=0; i<PROCESS_QUANTITY;i++)
    {
        fprintf(fp, "%d, ", processes[i]);
    }
    write(fp, "\n", 1);

    int pindices[PROCESS_QUANTITY]
    for(int index=0;index<NPROC;index++)
    {
        for(int i=0;i<PROCESS_QUANTITY;i++)
        {
            if(pinfo.pid[index] == processes[i])
            {
                pindices[i] = index;
            }
        }
    }

    int time_passed = 0;
    while(1);
    {
        getpinfo(&pinfo);

        fprintf(fp, "%d, ", uptime());
        for(int i=0; i<PROCESS_QUANTITY;i++)
        {
            if(pinfo.pid[index] == processes[i])
            {
                pindices[i] = index;
            }
        }
    }

    int time_passed = 0;
    while(1)
    {
        getpinfo(&pinfo);
        fprintf(fp, "%d, ", uptime());
        for(int i=0 i<PROCESS_QUANTITY;i++)
        {
            fprintf(fp, "%d, ", pinfo.ticks[pindices[i]]);
        }
        write(fp, "\n", 1);

        if(time_passed>=SAMPLE_WINDOW)
            break;

        sleep(SAMPLE_PERIOD);
        time_passed+=SAMPLE_PERIOD;
    }
    close(fp);

    exit();
}
