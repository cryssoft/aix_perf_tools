NOTES:

    hbaq         - requires root authority because of a lot of the system calls it leverages.
    
    lps_cpu      - partial re-do of some 'mpstat' output, very much a work in progress.
    lps_cputotal - ran this 24x7 on every LPAR in one environment.  lots of good data.
    lps_memplus  - ran this 24x7 on every LPAR in one environment.  lots of good data.
    lps_sea      - somewhat mis-named.  you can run it against an SEA or any bare Etherchannel device.

    i wouldn't call any of it more than "beta", since it's never been made available outside of
    operational environments yet.  i've run all of them 24x7 on AIX 7.2, 7.3 and VIOS 3.1, 4.1 without
    any difficulties or issues.  if you run lps_cputotal and lps_memplus on 5-second intervals 24x7,
    they usually take up aroun 5 seconds of CPU time per 24 hours.  the others are similar, so very low
    overhead.

    in cases, the sleep() or select() that sleeps between loops is absolute and not based on perfect
    intervals, so you'll see time creep/precession over time (sleep 5 seconds plus run for 0.001 seconds
    each loop means you gain 0.001 seconds every run).

USAGE:

    hbaq - uses older, HBAAPI calls, so HBAs are numbered from zero regardless of fcs# device names.
    
    run it against a particular HBA device (physical or virtual) with the "-d #" option to see all sorts
    of details of the HBA, ports under it (not exactly what we usually mean by ports), and open devices
    under them.  similar to the re-worked fcstat, but it can (caveats, disclaimers, etc.) show fabric
    ID and array port ID information that fcstat didn't the last time I checked.

    have you ever wondered how well-balanced your paths are?  run it with "-a # #", and it will give 
    you the same set of statistics for all cabled (or wrap-plugged) interfaces on a timed basis.  the
    last time I checked, this still worked for both physical and virtual HBAs.

    like some other tools, if you have HBA ports that are neither cabled to a live switch (or partner)
    and not wrap-plugged, they'll take a few seconds (each) to time out before the first loop.  i have
    not found a reliable way to eliminate that.

    lps_cpu - a partial re-write of "mpstat" based on trying to mimic the normal output with my own
    code.  not a lot of options here.  run it with the usual "# #" to set the interval and count of
    outputs.  however if you're team earl, you can try it with very small intervals (less than one
    second) and see if the data still makes sense.
    
    lps_cputotal - this uses other libperfstat calls to dump a ton of CPU-related metrics.  not a lot of
    options here.  run it with the usual "# #" to set the interval and count of outputs.  however if you're
    team earl, you can try it with very small intervals (less than one second) and see if the data still
    makes sense.
    
    lps_memplus - this uses libperfstat and other calls to dump a ton of memory-related metrics.  not a lot of
    options here.  run it with the usual "# #" to set the interval and count of outputs.  however if you're
    team earl, you can try it with very small intervals (less than one second) and see if the data still
    makes sense.

    lps_sea - similar to the other lps_* commands.  have you ever wondered how things are running across the
    various parts of a physical/virtual/SEA environment?  this can tell you in relatively real-time.  is the
    physical Etherchannel well-balanced?  you can see that.  how much is going physical<->virtual, you may be
    able to see that.  how much is going to/from each virtual interface?  you can see that.  sadly, when last
    I checked, there was no documented, callable interface to get the v-switch and VLAN information for 
    virtual NICs buried behind an Etherchannel or an SEA.  there is an undocumented interface I figured out
    for "bare" virtual NICs, but it changes for things behind another interface.  :-(  no, the last time I
    looked, it was not saved in the ODM.  :-(

    if memory serves, this command (using perfstat_bridgedadapter?) does work to show the same kind of data
    about a "bare" Etherchannel device (not behind an SEA) as well as for an SEA and everything behind it.
