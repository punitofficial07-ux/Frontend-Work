const input = document.getElementById('input');
input.readOnly = true; // Prevent direct typing
const buttons = document.querySelectorAll('button');

buttons.forEach(button => {
    button.addEventListener('click', () => {
        const value = button.textContent.trim();
        const img = button.querySelector('img');
        let action = '';

        if (img) {
            // Determine action based on image src
            const src = img.src;
            if (src.includes('delet.png')) {
                action = 'delete';
            } else if (src.includes('icons8-cancel-32.png')) {
                action = 'clear';
            } else if (src.includes('persentage.png')) {
                action = '%';
            } else if (src.includes('icons8-divide-50.png')) {
                action = '/';
            } else if (src.includes('icons8-multiply-50.png')) {
                action = '*';
            } else if (src.includes('icons8-minus-24.png')) {
                action = '-';
            } else if (src.includes('pluse.png')) {
                action = '+';
            } else if (src.includes('icons8-equal-sign-50.png')) {
                action = '=';
            }
        } else {
            action = value;
        }

        handleInput(action);
    });
});

// Keyboard input support
document.addEventListener('keydown', (e) => {
    let action = '';

    switch(e.key) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            action = e.key;
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
            action = e.key;
            break;
        case '.':
            action = '.';
            break;
        case 'Enter':
        case '=':
            action = '=';
            break;
        case 'Backspace':
            action = 'delete';
            break;
        case 'Escape':
        case 'c':
        case 'C':
            action = 'clear';
            break;
    }

    if (action) {
        e.preventDefault(); // Prevent default browser behavior
        handleInput(action);
    }
});

function handleInput(action) {
    if (action === 'clear') {
        input.value = '';
    } else if (action === 'delete') {
        input.value = input.value.slice(0, -1);
    } else if (action === '=') {
        try {
            input.value = eval(input.value);
        } catch {
            input.value = 'Error';
        }
    } else {
        input.value += action;
    }
}