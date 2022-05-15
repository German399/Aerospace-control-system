curl -L https://aka.ms/install-vsts-cli >cli-install
apt-get install libssl-dev libffi-dev python-dev build-essential
sha256sum cli-install
chmod 775 cli-install
./cli-install