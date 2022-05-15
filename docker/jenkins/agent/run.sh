docker build -t jenkins-agent-mskbo:latest .
docker run -d --rm --name=agent1 -p 202:22 \
-e "JENKINS_AGENT_SSH_PUBKEY=[pub_key_here]" \
jenkins-agent-mskbo:latest