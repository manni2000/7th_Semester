// Retrieve the form element
const form = document.getElementById('myForm');

// Listen for the form submission event
form.addEventListener('submit', function (event) {
    event.preventDefault(); // Prevent the default form submission

    // Retrieve the values from the form inputs
    const name = document.getElementById('name').value;
    const ID = document.getElementById('id').value;
    const cgpa = document.getElementById('cgpa').value;
    const dept = document.getElementById('department').value;
    const pref1 = document.getElementById('first_preference').value;
    const pref2 = document.getElementById('second_preference').value;
    const pref3 = document.getElementById('third_preference').value;



    // Create an object to store the form data
    const formData = {
        name: name,
        ID: ID,
        cgpa: cgpa,
        dept: dept,
        pref1: pref1,
        pref2: pref2,
        pref3: pref3
    };

    //   form.reset();
    const storedData = JSON.parse(localStorage.getItem('formData'));

    // Check if any data is already stored
    let updatedData = storedData || [];
    // Append the new form data to the existing data
    updatedData.push(formData);

    // Convert the updated form data to a JSON string
    const jsonData = JSON.stringify(updatedData);

    // Store the JSON string in the local storage
    localStorage.setItem('formData', jsonData);

    // Display a success message
    alert('Form data has been appended.');

    // Reset the form
    form.reset();
});