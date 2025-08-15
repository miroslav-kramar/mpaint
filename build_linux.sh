SOURCE="main.c app.c ui.c draw.c"
INCLUDE="-I../../raylib/include"
LIB="-L../../raylib/raylib-5.5_linux_amd64/lib -l:libraylib.a -lm"
WARNING="-Wall -Wextra -Wpedantic"
DEBUG="-fsanitize=address,undefined -g"

cd src/
gcc -o mpaint $SOURCE $INCLUDE $LIB $WARNING #$DEBUG
