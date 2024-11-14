/**
 * WEB222 – Assignment 3
 *
 * I declare that this assignment is my own work in accordance with
 * Seneca Academic Policy. No part of this assignment has been
 * copied manually or electronically from any other source
 * (including web sites) or distributed to other students.
 *
 * Please update the following with your information:
 *
 *      Name:       Ian Hartog
 *      Student ID: 163592199
 *      Date:       <SUBMISSION_DATE>
 */ // All of our data is available on the global `window` object.
// Create local variables to work with it in this file.
const { artists, songs } = window;
// For debugging, display all of our data in the console. You can remove this later.
console.log({
    artists,
    songs
}, "Song and Artist App Data");
document.addEventListener("DOMContentLoaded", function() {
    const menu = document.getElementById("menu");
    const selectedArtist = document.getElementById("selected-artist");
    const cardsContainer = document.querySelector(".cards-container");
    // Function to create song card
    function createSongCard(song) {
        // Create card element
        const card = document.createElement("div");
        card.className = "artist-card";
        // Create inner HTML for the card
        card.innerHTML = `
      <a href="${song.mediaUrl}" target="_blank">
        <img src="${song.imageUrl}" alt="${song.title} Image" class="artist-image">
      </a>
      <h3 class="song-title">${song.title}</h3>
      <time class="song-year">Year Recorded: ${song.released}</time>
      <span class="song-duration">Duration: ${Math.floor(song.duration / 60)}:${(song.duration % 60).toString().padStart(2, "0")}</span>
    `;
        return card;
    }
    // Function to show artist info and songs
    function showArtistInfo(artist) {
        selectedArtist.textContent = artist.name;
        // Clear existing cards
        cardsContainer.innerHTML = "";
        // Filter and display songs for the selected artist
        const filteredSongs = window.songs.filter((song)=>song.artistId === artist.artistId);
        filteredSongs.forEach((song)=>{
            // Create and append song card
            const songCard = createSongCard(song);
            cardsContainer.appendChild(songCard);
        });
    }
    // Create buttons for each artist
    window.artists.forEach((artist)=>{
        const button = document.createElement("button");
        button.textContent = artist.name;
        button.onclick = ()=>showArtistInfo(artist);
        menu.appendChild(button);
    });
    // Show the first artist's songs by default
    if (window.artists.length > 0) showArtistInfo(window.artists[0]);
});

//# sourceMappingURL=index.8f0c9192.js.map
