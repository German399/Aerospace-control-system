-# Установить debian live-образ серверного debian
-# Установить Docker <https://docs.docker.com/engine/install/debian/> и Docker-compose <https://docs.docker.com/compose/install/>, или любую их альтернативу(Kubernets)
-# Установить докер образы: portainer, gitea, jenkins, jenkins-agent-mskbo-build и registry
<IMG SRC="../../data/portainer.png"> <BR> 
Рисунок 1. Так выглядят запущенные контейнеры
-# Настроить службу доменных имен и прописать сертификаты для корректной работы ssl
-# Загрузить текущую версию проекта в систему контроля версий Gitea
<IMG SRC="../../data/gitea.png"> <BR> 
-# Настроить автоматическую сборку jenkins при помощи Gitea-plugin, используя докер сборочный образ jenkins-agent-mskbo-build
<IMG SRC="../../data/jenkins_plugin.png"> <BR> 
<IMG SRC="../../data/jenkins_autobuild.png"> <BR> 
-# Модуль ввода мскбо требует для работы программы xoutput(сборка для мскбо)/джойстика и кабины с запущенным WAGO