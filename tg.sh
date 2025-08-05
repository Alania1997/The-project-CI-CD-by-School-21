#!/bin/bash

BOT_TOKEN="7540068197:AAEzHWZdcp6XZVYCceUvh26H0ZH1x6Klmtc"

CHAT_ID="339508699"

# URL="https://api.telegram.org/bot${BOT_TOKEN}/sendMessage"

if [ "$CI_JOB_STATUS" == "success" ]; then
  MESSAGE="$CI_JOB_STAGE ✅"
else
  MESSAGE="$CI_JOB_STAGE 🚫"
fi

curl -s -X POST https://api.telegram.org/bot${BOT_TOKEN}/sendMessage -d chat_id=${CHAT_ID} -d text="${MESSAGE}" -d parse_mode="html"