# You're not using a posix-compliant shell. Fix that.
# Your shell: /bin/zsh
#
#!/usr/bin/sh
# it works on my system
# ( btw i use arch )

bin=()

bin+=( $( ls ./bin/ ) )

if test -d ./bin/; then
	for exe in ${bin[@]}
	do
		echo "Removing ./bin/$exe"
		rm ./bin/$exe
	done
fi

logs=()

logs+=( $(ls -a | grep .log) )

for log in ${logs[@]}; do
	echo "Removing $log."
	rm $log
done

out=()
out+=( $( ls -a | grep .out ) )

for out in ${out[@]}; do
	echo "Removing $out."
	rm $out
done
