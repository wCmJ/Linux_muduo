ps
pstree
pgrep       pgrep init
kill        ps -ef | grep redis | grep -v grep | awk '{print $2}' | xargs kill  /   kill -l
pkill       plill mysql     /   pkill -u hl
&           process1 &
jobs        
bg          bg %4
fg          fg %4
nice
runlevel

at          将任务排队，在指定的时间执行
atq         查看待执行的任务队列
atrm        从队列中删除待执行的任务

dmesg
free        查看内存使用情况
vmstat      虚拟内存统计
mpstat      CPU信息统计
pmap        查看进程使用内存情况      pmap processid
iostat      设备cpu和i/o统计信息
lspci       显示所有pci设备
ipcs
ipcrm



