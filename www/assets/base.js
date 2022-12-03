function navSetup() {
    document.getElementById("menu-btn")
        .onclick = function() {
            let sidenav = document.getElementById("sidenav");
            sidenav.classList.add("open");
        };
    document.getElementById("sidenav-close")
        .onclick = function() {
            let sidenav = document.getElementById("sidenav");
            sidenav.classList.remove("open");
        };
}

navSetup();
