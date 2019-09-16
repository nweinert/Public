function fillLabel(id) {
	$("#Slabel").val(id);
}

function fillGenre(id) {
	$("#Sgenre").val(id);
}

function fillArtist(id) {
	$("#Sartist").val(id);
}


function updateSong(id){
    $.ajax({
        url: '/songs/' + id,
        type: 'PUT',
        data: $('#updateSong').serialize(),
        success: function(result){
            window.location.replace("/songs");
        }
    })
};
