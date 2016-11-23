yasm --prefix=_ -p gas -f win32 -D BUILD_X86_HOST ..\arch\x86_host\exceptions.s -o obj\exceptions_x86_host.obj
yasm --prefix=_ -p gas -f win32 -D BUILD_X86_HOST ..\arch\x86_host\context.s -o obj\context_x86_host.obj
