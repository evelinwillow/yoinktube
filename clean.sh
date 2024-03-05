# You're not using a posix-compliant shell. Fix that.
# Your shell: /bin/zsh
#
#!/usr/bin/sh
# it works on my system
# ( btw i use arch )
if test -d bin/; then
	if test -f bin/out; then
		rm bin/out
	fi
fi
