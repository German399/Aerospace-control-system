%Необходимо скачать https://github.com/dantswain/redis-matlab
%данная библиотека кладется в папку с проектом simulink
%добавляется блок в симулинк Interpreted matlab function
function joyOut = redis_get_joi(u)
%global R;

addpath('./redis-matlab-master/src/');
R=redisConnection('mskbo.local.bmstu.ru',49153);
%[R, Status] = redisSet(R, 'foo', 'bar'); % Status = 'OK'
[Ans, R, Status]=redisGet(R,'X');
X =str2double(strrep(Ans,',','.'));
[Ans, R, Status]=redisGet(R,'Y');
Y =str2double(strrep(Ans,',','.'));
[Ans, R, Status]=redisGet(R,'Z');
Z =str2double(strrep(Ans,',','.'));
joyOut = [X,Y,Z];
redisDisconnect(R);
%y = u;