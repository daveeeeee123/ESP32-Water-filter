import { initializeApp } from "https://www.gstatic.com/firebasejs/11.6.0/firebase-app.js";
import { getDatabase, ref, onValue } from "https://www.gstatic.com/firebasejs/11.6.0/firebase-database.js";

// Firebase configuration
const firebaseConfig = {
    apiKey: "AIzaSyDUB8w_0fsAuj8kv3aJEqgErY5RtPobKUc",
    authDomain: "esp-32-c2cd8.firebaseapp.com",
    databaseURL: "https://esp-32-c2cd8-default-rtdb.asia-southeast1.firebasedatabase.app",
    projectId: "esp-32-c2cd8",
    storageBucket: "esp-32-c2cd8.firebasestorage.app",
    messagingSenderId: "581754015417",
    appId: "1:581754015417:web:2af670c9568967d07ed568"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);

// Get a reference to the database
const database = getDatabase(app);

// Database Paths
const dataFloatPath = 'test/float';
const dataIntPath = 'test/int';
const dataStringPath = 'test/string';

// Get database references
const databaseFloatRef = ref(database, dataFloatPath);
const databaseIntRef = ref(database, dataIntPath);
const databaseStringRef = ref(database, dataStringPath);

// Variables to save database current values
let floatReading;
let intReading;
let stringReading;

// Attach listeners
onValue(databaseFloatRef, (snapshot) => {
    floatReading = snapshot.val();
    console.log("Float reading: " + floatReading);
    document.getElementById("reading-float").innerHTML = floatReading;
});

onValue(databaseIntRef, (snapshot) => {
    intReading = snapshot.val();
    console.log("Int reading: " + intReading);
    document.getElementById("reading-int").innerHTML = intReading;
});

onValue(databaseStringRef, (snapshot) => {
    stringReading = snapshot.val();
    console.log("String reading: " + stringReading);
    document.getElementById("reading-string").innerHTML = stringReading;
});