async function handleNameSubmit(event) {
    event.preventDefault();

    const nameInput = document.querySelector("#name");
    if (!nameInput) {
        return;
    }

    try {
        const response = await fetch("/greetingIPC", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({
                name: nameInput.value
            })
        });

        if (!response.ok) {
            throw new Error(`Request failed with status ${response.status}`);
        }

        const responseText = await response.text();
        if (!responseText) {
            throw new Error("Endpoint returned an empty response body.");
        }

        const responseBody = JSON.parse(responseText);
        if (typeof responseBody.greeting !== "string") {
            throw new Error("Endpoint response is missing the 'greeting' string.");
        }

        alert(responseBody.greeting);
    }
    catch (error) {
        alert(error instanceof Error ? error.message : "Greeting request failed.");
    }
}