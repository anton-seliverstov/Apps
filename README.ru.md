Apps
======

apps - Удобное консольное "Меню Приложений" для Unix и Linux.

Большинство утилит и приложений для командной строки имеют 
труднозапоминающиеся названия не только для новичков, но и опытных системных администраторов... 
особенно если не пользоваться ими некоторое время.
Это простое меню поможет Вам объединить под одной крышей все ваши консольные 
приложения и распределить их по понятным категориям.

Больше не нужно держать в голове все эти сумасшедшие названия и флаги,
единственная команда, которую нужно помнить, входя в консоль - это "apps"!

Добавьте в меню команду с нужными параметрами, дайте ей простое название
и оставьте комментарий с описанием, что она делает.
Перемещайтесь по меню стрелками, или любыми другими кнопками.
Удобно!

Установка
-----------

TravisCI: ![#](https://travis-ci.org/anton-seliverstov/Apps.svg?branch=master)
```
git clone https://github.com/anton-seliverstov/Apps.git Apps
cd Apps
git submodule init
git submodule update
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
echo "User friendly console Applications Menu for Unix & Linux" | checkinstall -D --install="no" --pkgname "apps" --pkgversion "1.0" --pkgarch "amd64" --pkgrelease "1" --pkgsource "https://github.com/anton-seliverstov/Apps.git" --pkggroup "misc" --pkglicense "GNU General Public License, Version 3" --install=no --nodoc
dpkg -i apps_1.0-1_amd64.deb
```

Пример
-------

Чобы создать простенький шаблон для вашего меню, просто запустите 
```
apps
```

Чтобы собрать меню на основе установленных приложений запустите
```
generate_apps-rc
```

У меню очень простой XML-подобный синтаксис, 
взгляните на этот пример:
```
<apps >
    <prop name="SHOW_COMMENTS" value="true"/>

    <folder name="root">
        <folder name="утилиты" >
            <app name="показать IP" cmd="/sbin/ifconfig" comment="показивает вывод ifconfig нерутовому пользователю" />
        </folder>
    </folder>
</apps >
```
## License

GNU General Public License, Version 3

