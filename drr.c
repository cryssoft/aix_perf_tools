#include  <errno.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <time.h>
#include  <unistd.h>
#include  <sys/signal.h>
#include  <sys/dr.h>


#define  E_sysErrno  errno

static int gs_phase;


char *xlateDrOp (unsigned short l_drOperation)
{
  static char *l_returnValue;


  l_returnValue = (static char *) "(unknown)";

  switch (l_drOperation)
  {
    case DR_OP_ENT_MEM_CAP_ADD :
      l_returnValue = (static char *) "ent. memory capacity add";
      break;
    case DR_OP_ENT_MEM_CAP_REMOVE :
      l_returnValue = (static char *) "ent. memory capacity remove";
      break;
    case DR_OP_VAR_MEM_CAP_ADD :
      l_returnValue = (static char *) "var. memory capacity add";
      break;
    case DR_OP_VAR_MEM_CAP_REMOVE :
      l_returnValue = (static char *) "var. memory capacity remove";
      break;
    case DR_OP_CPU_AFFINITY_REFRESH :
      l_returnValue = (static char *) "CPU affinity refresh";
      break;
    case DR_OP_AME_FACTOR :
      l_returnValue = (static char *) "AME factor";
      break;
    case DR_OP_PHIB :
      l_returnValue = (static char *) "PHIB";
      break;
    case DR_OP_ACC :
      l_returnValue = (static char *) "ACC";
      break;
    case DR_OP_CHLMB_AFF :
      l_returnValue = (static char *) "CHLMB AFF";
      break;
    case DR_OP_LVUPD :
      l_returnValue = (static char *) "LVUPD";
      break;
  }

  return (l_returnValue);
}


void  handleSigReconfig (int p_signalID)
{
  char       l_nowBuf[32];
  dr_info_t  l_drInfo;
  int        l_callReturns;
  int        l_lclErrno;
  time_t     l_now;


  (void) time (&l_now);
  (void) strftime (l_nowBuf, 32, "%Y/%m/%d %H:%M:%S", localtime (&l_now));
  (void) fprintf (stdout, "handleSigReconfig - query - phase %d at %s\n", gs_phase, l_nowBuf);
  if ((l_callReturns = dr_reconfig (DR_QUERY, &l_drInfo)) == 0)
  {
    (void) fprintf (stdout, "add         flag %d\n", (int) l_drInfo.add);
    (void) fprintf (stdout, "remove      flag %d\n", (int) l_drInfo.rem);
    (void) fprintf (stdout, "CPU         flag %d\n", (int) l_drInfo.cpu);
    (void) fprintf (stdout, "memory      flag %d\n", (int) l_drInfo.mem);
    (void) fprintf (stdout, "\n");
    (void) fprintf (stdout, "check      phase %d\n", (int) l_drInfo.check);
    (void) fprintf (stdout, "pre        phase %d\n", (int) l_drInfo.pre);
    (void) fprintf (stdout, "doit       phase %d\n", (int) l_drInfo.doit);
    (void) fprintf (stdout, "post       phase %d\n", (int) l_drInfo.post);
    (void) fprintf (stdout, "error      phase %d\n", (int) l_drInfo.posterror);
    (void) fprintf (stdout, "\n");
    (void) fprintf (stdout, "bindproc    flag %d\n", (int) l_drInfo.bindproc);
    (void) fprintf (stdout, "softpset    flag %d\n", (int) l_drInfo.softpset);
    (void) fprintf (stdout, "hardpset    flag %d\n", (int) l_drInfo.hardpset);
    (void) fprintf (stdout, "plock       flag %d\n", (int) l_drInfo.plock);
    (void) fprintf (stdout, "pshm        flag %d\n", (int) l_drInfo.pshm);
    (void) fprintf (stdout, "ent_cap     flag %d\n", (int) l_drInfo.ent_cap);
    (void) fprintf (stdout, "var_wgt     flag %d\n", (int) l_drInfo.var_wgt);
    (void) fprintf (stdout, "\n");
    (void) fprintf (stdout, "capable     flag %d\n", (int) l_drInfo.var_wgt);
    (void) fprintf (stdout, "shared      flag %d\n", (int) l_drInfo.var_wgt);
    (void) fprintf (stdout, "capped      flag %d\n", (int) l_drInfo.var_wgt);
    (void) fprintf (stdout, "constr      flag %d\n", (int) l_drInfo.var_wgt);
    (void) fprintf (stdout, "\n");
    (void) fprintf (stdout, "migrate     flag %d\n", (int) l_drInfo.migrate);
    (void) fprintf (stdout, "hibernate   flag %d\n", (int) l_drInfo.hibernate);
    (void) fprintf (stdout, "partition   flag %d\n", (int) l_drInfo.partition);
    (void) fprintf (stdout, "WPAR        flag %d\n", (int) l_drInfo.workload_partition);
    (void) fprintf (stdout, "checkpoint  flag %d\n", (int) l_drInfo.checkpoint);
    (void) fprintf (stdout, "restart     flag %d\n", (int) l_drInfo.restart);
    (void) fprintf (stdout, "topology    flag %d\n", (int) l_drInfo.topology_update);
    (void) fprintf (stdout, "acc_update  flag %d\n", (int) l_drInfo.acc_update);
    (void) fprintf (stdout, "chlmb       flag %d\n", (int) l_drInfo.chlmb);
    (void) fprintf (stdout, "\n");
    (void) fprintf (stdout, "lcpu             %d\n", (int) l_drInfo.lcpu);
    (void) fprintf (stdout, "bcpu             %d\n", (int) l_drInfo.bcpu);
    (void) fprintf (stdout, "\n");
    (void) fprintf (stdout, "phase_gen        %u\n", l_drInfo.phase_gen);
    (void) fprintf (stdout, "\n");
    (void) fprintf (stdout, "req_memsz_chg    %llu\n", l_drInfo.req_memsz_change);
    (void) fprintf (stdout, "sys_memsz        %llu\n", l_drInfo.sys_memsz);
    (void) fprintf (stdout, "sys_free_frames  %lld\n", l_drInfo.sys_free_frames);
    (void) fprintf (stdout, "sys_pin_frames   %lld\n", l_drInfo.sys_pinnable_frames);
    (void) fprintf (stdout, "sys_total_frames %lld\n", l_drInfo.sys_total_frames);
    (void) fprintf (stdout, "\n");
    (void) fprintf (stdout, "capacity         %llu\n", l_drInfo.capacity);
    (void) fprintf (stdout, "delta_cap        %d\n",   l_drInfo.delta_cap);
    (void) fprintf (stdout, "dr_op            %hu (%s)\n",   l_drInfo.dr_op, xlateDrOp (l_drInfo.dr_op));
    (void) fprintf (stdout, "\n");
    (void) fprintf (stdout, "mem_capacity     %llu\n", l_drInfo.mem_capacity);
    (void) fprintf (stdout, "delta_mem_cap    %lld\n", l_drInfo.delta_mem_capacity);
    (void) fprintf (stdout, "\n");

    (void) fprintf (stdout, "handleSigReconfig - query|done - phase %d\n", gs_phase);
    if ((l_callReturns = dr_reconfig (DR_QUERY | DR_RECONFIG_DONE, &l_drInfo)) == 0)
    {
      (void) fprintf (stdout, "handleSigReconfig - done - phase %d\n", gs_phase);
    }
    else
    {
      l_lclErrno = E_sysErrno;
      (void) fprintf (stderr, "\n");
      (void) fprintf (stderr, "ERROR:  First dr_reconfig() failed\n");
      (void) fprintf (stderr, "ERROR:  (%d) %s\n", l_lclErrno, strerror (l_lclErrno));
      (void) fprintf (stderr, "\n");
    }
  }
  else
  {
    l_lclErrno = E_sysErrno;
    (void) fprintf (stderr, "\n");
    (void) fprintf (stderr, "ERROR:  First dr_reconfig() failed\n");
    (void) fprintf (stderr, "ERROR:  (%d) %s\n", l_lclErrno, strerror (l_lclErrno));
    (void) fprintf (stderr, "\n");
  }

  (void) fprintf (stdout, "\n");
  (void) fprintf (stdout, "\n");
  (void) fflush  (stdout);
  gs_phase++;
  return;
}


int main (int p_argc, char **p_argv)
{
  gs_phase = 1;

  while ( 1 )
  {
    (void) signal (SIGRECONFIG, handleSigReconfig);
    (void) fprintf (stdout, "MAIN:  signal handler installed (1) - sleeping\n");
    (void) sleep (1024);
  }

  return (0);
}
