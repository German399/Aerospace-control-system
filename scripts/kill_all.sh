      ps aux  |  grep -i OU_exe  |  awk '{print $2}'  |  xargs kill -9   
      ps aux  |  grep -i FPZ_exe |  awk '{print $2}'  |  xargs kill -9   
      ps aux  |  grep -i KSU_exe  |  awk '{print $2}'  |  xargs kill -9   
      ps aux  |  grep -i LA_exe  |  awk '{print $2}'  |  xargs kill -9   
      ps aux  |  grep -i INS_exe  |  awk '{print $2}'  |  xargs kill -9   
      ps aux  |  grep -i SVS_exe  |  awk '{print $2}'  |  xargs kill -9   

      ps aux  |  grep -i IUP_exe  |  awk '{print $2}'  |  xargs kill -9   
      ps aux  |  grep -i MSKBO_multi_exec  |  awk '{print $2}'  |  xargs kill -9