function deleteRelation(id, artistId){
    $.ajax({
        url: '/delete_relation/' + id + '&' + artistId,
        type: 'DELETE',
        success: function(result){
            window.location.reload(true);
        }
    })
};
function deleteRelationGenre(id, genreId){
    $.ajax({
        url: '/delete_relation/genre/' + id + '&' +genreId,
        type: 'GET',
        success: function(result){
            window.location.reload(true);
        }
    })
};
