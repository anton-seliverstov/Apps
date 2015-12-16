Apps
======

    apps - User friendly console "Applications Menu" for Unix & Linux.

    Most command-line tools and applications have names that are hard to remember
    not only for new users but also for experienced system administrators, 
    when they don't use some console command for a while.
    This simple menu will help you to collect all your console applications
    under one roof and sort them by meaningful categories.

    No need to keep all that crazy names and flags in your head,
    the only thing that you need to remember when running console - is "apps"!

    Add command with all your favorite flags to menu, put some easy name for it
    and leave a comment with description of what it's doing.
    Run apps and navigate menu with arrows or whatever buttons you like.
    Handy!

Installation
-----------

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

Example
-------

    To build a sample menu template, simply run
```
    apps
```

    To generate menu based on installed applications run
```
    generate_apps-rc
```

    Menu has an easy to understand XML-like syntax, 
    take a look at this example:
```
<apps >
    <prop name="SHOW_COMMENTS" value="true"/>

    <folder name="root">
        <folder name="utils" >
            <app name="show IP" cmd="/sbin/ifconfig" comment="shows ifconfig info to non-root user" />
        </folder>
    </folder>
</apps >
```
## License

    GNU General Public License, Version 3

