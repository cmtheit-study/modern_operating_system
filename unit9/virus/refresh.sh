for s in $(find ./victim-dir -type f -name "*.c")
do
  gcc "$s" -o "${s%.*}"
done