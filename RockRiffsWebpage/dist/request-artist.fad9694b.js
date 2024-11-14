function validateNewsletterForm() {
    const email = document.querySelector('input[name="email"]').value;
    if (!email) {
        alert("Please enter a valid email address.");
        return false;
    }
    return true;
}
function validateArtistForm() {
    const artistName = document.getElementById("artist-name").value;
    const genre = document.getElementById("genre").value;
    const description = document.getElementById("description").value;
    if (!artistName || !genre || !description) {
        alert("Please fill out all required fields.");
        return false;
    }
    return true;
}
function addSongUrlInput() {
    const container = document.getElementById("song-urls-container");
    const input = document.createElement("input");
    input.type = "url";
    input.name = "song-urls[]";
    container.appendChild(input);
}

//# sourceMappingURL=request-artist.fad9694b.js.map
