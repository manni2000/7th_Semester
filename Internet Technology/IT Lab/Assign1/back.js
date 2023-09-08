// Retrieve the table element
const table = document.getElementById('myTable');

// Retrieve stored form data from localStorage
const storedData = JSON.parse(localStorage.getItem('formData'));

// Check if any data is stored
if (storedData && storedData.length > 0) {
    // Iterate over the stored data and populate the table
    storedData.forEach(function (data) {
        const name = data.name;
        const ID = data.ID;
        const cgpa = data.cgpa;
        const dept = data.dept;
        const pref1 = data.pref1;
        const pref2 = data.pref2;
        const pref3 = data.pref3;

        // Create a new row
        const row = table.insertRow();

        // Insert cells with the data
        const nameCell = row.insertCell();
        nameCell.textContent = name;
        const IDCell = row.insertCell();
        IDCell.textContent = ID;
        const cgpaCell = row.insertCell();
        cgpaCell.textContent = cgpa;
        const deptCell = row.insertCell();
        deptCell.textContent = dept;
        const pref1Cell = row.insertCell();
        pref1Cell.textContent = pref1;
        const pref2Cell = row.insertCell();
        pref2Cell.textContent = pref2;
        const pref3Cell = row.insertCell();
        pref3Cell.textContent = pref3;
    });
}