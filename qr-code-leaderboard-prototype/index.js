// Parse URL parameters
      const params = new URLSearchParams(window.location.search);
      const tableBody = document.querySelector("#userTable tbody");

      params.forEach((value, key) => {
        const row = document.createElement("tr");
        const keyCell = document.createElement("td");
        const valueCell = document.createElement("td");
        keyCell.textContent = key;
        valueCell.textContent = value;
        row.appendChild(keyCell);
        row.appendChild(valueCell);
        tableBody.appendChild(row);
      });