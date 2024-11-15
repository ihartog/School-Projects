const fs = require('fs').promises;
const path = require('path');

let items = [];
let categories = [];

function initialize() {
    return new Promise(async (resolve, reject) => {
        try {
            // Read items.json
            const itemsData = await fs.readFile(path.join(__dirname, 'data', 'items.json'), 'utf8');
            items = JSON.parse(itemsData);

            // Read categories.json
            const categoriesData = await fs.readFile(path.join(__dirname, 'data', 'categories.json'), 'utf8');
            categories = JSON.parse(categoriesData); 

            resolve('Data successfully initialized');
        } catch (error) {
            reject('Unable to read file: ' + error.message);
        }
    });
}

function getAllItems() {
    return new Promise((resolve, reject) => {
        if (items.length > 0) {
            resolve(items);
        } else {
            reject('No results returned');
        }
    });
}

function getPublishedItems() {
    return new Promise((resolve, reject) => {
        const publishedItems = items.filter(item => item.published);
        if (publishedItems.length > 0) {
            resolve(publishedItems);
        } else {
            reject('No results returned');
        }
    });
}

function getCategories() {
    return new Promise((resolve, reject) => {
        if (categories.length > 0) {
            resolve(categories);
        } else {
            reject('No results returned');
        }
    });
}

module.exports = {
    initialize,
    getAllItems,
    getPublishedItems,
    getCategories
};
