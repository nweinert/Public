function deleteSong(id){
    $.ajax({
        url: '/songs/' + id,
        type: 'DELETE',
        success: function(result){
            window.location.reload(true);
        }
    })
};
function deleteSongArtist(id, artistId){
    $.ajax({
        url: '/songs_artists/id/' + id + '/artists/' + artistId,
        type: 'DELETE',
        success: function(result){
            if(result.responseText != undefined){
              alert(result.responseText)
            }
            else {
              window.location.reload(true)
            } 
        }
    })
  };
  