file_path="test.txt"
if [ -f ${file_path} ]; then

  exec 9>> ${file_path}
  while true; do
    if flock -n 9; then
       echo "文件已加锁"
       break
    else
      sleep 1
      echo "获取文件锁失败"
    fi
  done
  last_line=$(tail -n 1 ${file_path})
  last_number=$(echo ${last_line} | grep -oE '[0-9]+')
  next_number=$((last_number + 1))
  echo "${next_number}" >> ${file_path}
  flock -u 9
else
  touch ${file_path}
  echo "1" >> ${file_path}
fi
