function filterSongsByGenre() {
    //get the id of the selected genres from the filter dropdown
    var genreId = document.getElementById('genreFilter').value;
    //construct the URL and redirect to it
    window.location = '/songs/genre/' + parseInt(genreId);
}

function filterSongsByArtist() {
    //get the id of the selected genres from the filter dropdown
    var artistId = document.getElementById('artistFilter').value;
    //construct the URL and redirect to it
    window.location = '/songs/artist/' + parseInt(artistId);
}

