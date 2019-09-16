function filterArtistByGenre() {
    //get the id of the selected genres from the filter dropdown
    var genreId = document.getElementById('artistFilter').value;
    //construct the URL and redirect to it
    window.location = '/artist/filter/' + parseInt(genreId);
}
