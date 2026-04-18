const mobileMenuButton = document.querySelector('.mobile-menu-button');
const navLinks = document.querySelector('.nav-links');
const orderButtons = document.querySelectorAll('.order-btn');
const subscribeForm = document.getElementById('subscribe-form');
const notification = document.querySelector('.notification');
const coffeeSearchInput = document.getElementById('coffee-search');
const coffeePreviewButton = document.getElementById('coffee-preview-btn');
const coffeePreviewImage = document.getElementById('coffee-preview-image');
const coffeePreviewName = document.getElementById('coffee-preview-name');
const coffeePreviewDescription = document.getElementById('coffee-preview-description');
const typeCards = document.querySelectorAll('.type-card');


const coffeeData = {
    espresso: {
        image: './Images/Expresso.jpg',
        title: 'Espresso',
        description: 'A bold shot of concentrated coffee with rich crema and intense flavor.'
    },
    latte: {
        image: './Images/Coffe.png',
        title: 'Latte',
        description: 'Smooth espresso combined with steamed milk and a creamy layer of foam.'
    },
    cappuccino: {
        image: './Images/capachino.jpg',
        title: 'Cappuccino',
        description: 'Balanced espresso drink topped with thick milk foam and velvety texture.'
    },
    mocha: {
        image: './Images/ChaiLatte.jpg',
        title: 'Mocha',
        description: 'Espresso blended with chocolate and steamed milk for a sweet, cozy treat.'
    }
};

function showNotification(message) {
    if (!notification) return;
    notification.textContent = message;
    notification.classList.add('visible');
    setTimeout(() => {
        notification.classList.remove('visible');
    }, 2600);
}

function showCoffeePreview(coffeeKey) {
    const coffee = coffeeData[coffeeKey.toLowerCase()];
    if (!coffee) {
        showNotification('Sorry, that coffee is not available. Try espresso, latte, cappuccino, or mocha.');
        return;
    }

    coffeePreviewImage.src = coffee.image;
    coffeePreviewImage.alt = coffee.title;
    coffeePreviewName.textContent = coffee.title;
    coffeePreviewDescription.textContent = coffee.description;
    showNotification(`${coffee.title} selected!`);
}

mobileMenuButton?.addEventListener('click', () => {
    navLinks?.classList.toggle('open');
});

orderButtons.forEach(button => {
    button.addEventListener('click', () => {
        const item = button.dataset.item || 'item';
        showNotification(`${item} added to your order!`);
    });
    button.addEventListener('keydown', (event) => {
        if (event.key === 'Enter' || event.key === ' ') {
            event.preventDefault();
            const item = button.dataset.item || 'item';
            showNotification(`${item} added to your order!`);
        }
    });
});

typeCards.forEach(card => {
    card.addEventListener('click', () => {
        const coffeeName = card.dataset.coffee;
        if (coffeeName) {
            showCoffeePreview(coffeeName);
        }
    });
});

coffeePreviewButton?.addEventListener('click', () => {
    const query = coffeeSearchInput?.value.trim();
    if (query) {
        showCoffeePreview(query);
    }
});

coffeeSearchInput?.addEventListener('keydown', (event) => {
    if (event.key === 'Enter') {
        event.preventDefault();
        const query = coffeeSearchInput.value.trim();
        if (query) {
            showCoffeePreview(query);
        }
    }
});

subscribeForm?.addEventListener('submit', (event) => {
    event.preventDefault();
    const email = subscribeForm.email.value.trim();
    if (!email) {
        showNotification('Please enter a valid email address.');
        return;
    }
    subscribeForm.reset();
    showNotification('Thanks! You are subscribed.');
    localStorage.setItem('subscribedEmail', email);
});
