document.addEventListener("DOMContentLoaded", () => {

    // --- API Endpoints ---
    const PERSONAL_API = 'http://localhost/cgi-bin/personal.exe';
    const EDUCATION_API = 'http://localhost/cgi-bin/education.exe';
    const SKILLS_API = 'http://localhost/cgi-bin/skills.exe';
    const ACHIEVEMENTS_API = 'http://localhost/cgi-bin/achievements.exe';
    const ADDITIONAL_API = 'http://localhost/cgi-bin/additional.exe';
    const JOB_CYCLE_API = 'http://localhost/cgi-bin/job_cycle.exe';

    // --- Helper function to clear inputs ---
    function clearInputs(fieldIds) {
        fieldIds.forEach(id => {
            const element = document.getElementById(id);
            if (element) {
                element.value = '';
            }
        });
    }

    // --- Helper: Create Preview Card ---
    function createPreviewCard(index, contentHtml) {
        const card = document.createElement('div');
        card.className = 'preview-card';
        card.innerHTML = `<span class="preview-card-index">${index}:</span>
                          <div class="preview-card-content">${contentHtml}</div>`;
        return card;
    }


    // == 1. PERSONAL DETAILS SCRIPTING

    
    // --- Render Personal Details ---
    function renderPersonalPreview(dataArray) {
        const previewDiv = document.getElementById('pd-preview-area');
        previewDiv.innerHTML = ''; 
        if (!dataArray || dataArray.length === 0) {
            previewDiv.innerHTML = '<p class="placeholder">Click the title above to load initial fields or refresh preview.</p>';
            return;
        }
        dataArray.forEach((item, index) => {
            const content = `<strong>${item.field} :</strong> <span>${item.value || '(empty)'}</span>`;
            previewDiv.appendChild(createPreviewCard(index, content));
        });
    }

    // --- Get Personal Details ---
    async function getPersonalPreview() {
        try {
            const payload = { action: "preview" };
            const response = await fetch(PERSONAL_API, { method: 'POST', body: JSON.stringify(payload) });
            if (!response.ok) throw new Error(`HTTP error! status: ${response.status}`);
            const data = await response.json();
            renderPersonalPreview(data);
        } catch (error) {
            console.error('Error fetching personal details:', error);
            document.getElementById('pd-preview-area').innerHTML = '<p class="placeholder error">Error loading data. Is the backend running?</p>';
        }
    }

    // --- Action: Initialize (Attached to Title) ---
    document.getElementById('init-title').onclick = async () => {
        try {
            const payload = { action: "init" };
            const response = await fetch(PERSONAL_API, { method: 'POST', body: JSON.stringify(payload) });
             if (!response.ok) throw new Error(`HTTP error! status: ${response.status}`);
            const data = await response.json();
            renderPersonalPreview(data);
        } catch (error) {
            console.error('Error initializing personal details:', error);
             document.getElementById('pd-preview-area').innerHTML = '<p class="placeholder error">Error initializing data.</p>';
        }
    };

    // --- Button: Refresh Preview ---
    document.getElementById('pd-preview').onclick = getPersonalPreview;

    // --- Button: Add ---
    document.getElementById('pd-add-btn').onclick = async () => {
        const indexInput = document.getElementById('pd-add-index');
        const payload = {
            action: "add",
            data: {
                field: document.getElementById('pd-add-field').value || 'New Field',
                value: document.getElementById('pd-add-value').value || '',
                index: parseInt(indexInput.value) >= 0 ? parseInt(indexInput.value) : 999 // Append if index is invalid
            }
        };
        try {
            await fetch(PERSONAL_API, { method: 'POST', body: JSON.stringify(payload) });
            clearInputs(['pd-add-field', 'pd-add-value', 'pd-add-index']);
            getPersonalPreview();
        } catch (error) {
            console.error('Error adding personal detail:', error);
            alert('Error adding field. Check console.');
        }
    };
    
    // --- Button: Update ---
    document.getElementById('pd-upd-btn').onclick = async () => {
        const indexInput = document.getElementById('pd-upd-index');
        const payload = {
            action: "update",
            data: {
                index: parseInt(indexInput.value),
                value: document.getElementById('pd-upd-value').value
            }
        };
        if (isNaN(payload.data.index) || payload.data.index < 0) {
            alert("Please enter a valid index to update.");
            return;
        }
         try {
            await fetch(PERSONAL_API, { method: 'POST', body: JSON.stringify(payload) });
            clearInputs(['pd-upd-index', 'pd-upd-value']);
            getPersonalPreview();
        } catch (error) {
             console.error('Error updating personal detail:', error);
            alert('Error updating field. Check console.');
        }
    };

    // --- Button: Remove ---
    document.getElementById('pd-del-btn').onclick = async () => {
         const indexInput = document.getElementById('pd-del-index');
        const payload = {
            action: "remove",
            data: { index: parseInt(indexInput.value) }
        };
         if (isNaN(payload.data.index) || payload.data.index < 0) {
            alert("Please enter a valid index to delete.");
            return;
        }
        try {
            await fetch(PERSONAL_API, { method: 'POST', body: JSON.stringify(payload) });
            clearInputs(['pd-del-index']);
            getPersonalPreview();
        } catch (error) {
             console.error('Error deleting personal detail:', error);
            alert('Error deleting field. Check console.');
        }
    };


    // == 2. EDUCATION SCRIPTING


    // --- Render Education ---
    function renderEducationPreview(dataArray) {
        const previewDiv = document.getElementById('edu-preview-area');
        previewDiv.innerHTML = '';
        if (!dataArray || dataArray.length === 0) {
            previewDiv.innerHTML = "<p class='placeholder'>No education entries added.</p>";
            return;
        }
        dataArray.forEach((item, index) => {
            const content = `<strong>${item.name}</strong>
                             <span>${item.course_year}</span>
                             <span>Score: ${item.score || 'N/A'}</span>`;
            previewDiv.appendChild(createPreviewCard(index, content));
        });
    }

    // --- Get Education ---
    async function getEducationPreview() {
         try {
            const payload = { action: "preview" };
            const response = await fetch(EDUCATION_API, { method: 'POST', body: JSON.stringify(payload) });
             if (!response.ok) throw new Error(`HTTP error! status: ${response.status}`);
            const data = await response.json();
            renderEducationPreview(data);
        } catch (error) {
             console.error('Error fetching education details:', error);
             document.getElementById('edu-preview-area').innerHTML = '<p class="placeholder error">Error loading data.</p>';
        }
    }

    // --- Button: Refresh ---
    document.getElementById('edu-preview').onclick = getEducationPreview;

    // --- Button: Add ---
    document.getElementById('edu-add-btn').onclick = async () => {
        const indexInput = document.getElementById('edu-add-index');
        const scoreInput = document.getElementById('edu-add-score').value;
        const payload = {
            action: "add",
            data: {
                name: document.getElementById('edu-add-name').value || 'School/University',
                course_year: document.getElementById('edu-add-course').value || 'Degree, Year',
                score: scoreInput ? parseFloat(scoreInput) : 0.0,
                index: parseInt(indexInput.value) >= 0 ? parseInt(indexInput.value) : 999
            }
        };
        try {
            await fetch(EDUCATION_API, { method: 'POST', body: JSON.stringify(payload) });
            clearInputs(['edu-add-name', 'edu-add-course', 'edu-add-score', 'edu-add-index']);
            getEducationPreview();
        } catch (error) {
            console.error('Error adding education detail:', error);
            alert('Error adding education. Check console.');
        }
    };

    // --- Button: Remove ---
    document.getElementById('edu-del-btn').onclick = async () => {
         const indexInput = document.getElementById('edu-del-index');
        const payload = {
            action: "remove",
            data: { index: parseInt(indexInput.value) }
        };
        if (isNaN(payload.data.index) || payload.data.index < 0) {
            alert("Please enter a valid index to delete.");
            return;
        }
        try {
            await fetch(EDUCATION_API, { method: 'POST', body: JSON.stringify(payload) });
            clearInputs(['edu-del-index']);
            getEducationPreview();
        } catch (error) {
            console.error('Error deleting education detail:', error);
            alert('Error deleting education. Check console.');
        }
    };



    // == 3. SKILLS SCRIPTING


     // --- Render Skills ---
    function renderSkillsPreview(dataArray) {
        const previewDiv = document.getElementById('skl-preview-area');
        previewDiv.innerHTML = '';
        if (!dataArray || dataArray.length === 0) {
            previewDiv.innerHTML = "<p class='placeholder'>No skills enqueued.</p>";
            return;
        }
        dataArray.forEach((item, index) => {
            const content = `<strong>${item.skill}</strong>`;
            previewDiv.appendChild(createPreviewCard(index, content));
        });
    }

    // --- Get Skills ---
    async function getSkillsPreview() {
         try {
            const payload = { action: "preview" };
            const response = await fetch(SKILLS_API, { method: 'POST', body: JSON.stringify(payload) });
            if (!response.ok) throw new Error(`HTTP error! status: ${response.status}`);
            const data = await response.json();
            renderSkillsPreview(data);
        } catch (error) {
             console.error('Error fetching skills:', error);
             document.getElementById('skl-preview-area').innerHTML = '<p class="placeholder error">Error loading data.</p>';
        }
    }

    // --- Button: Refresh ---
    document.getElementById('skl-preview').onclick = getSkillsPreview;

    // --- Button: Add (Enqueue) ---
    document.getElementById('skl-add-btn').onclick = async () => {
        const skillInput = document.getElementById('skl-add-skill').value;
        if (!skillInput) {
            alert('Please enter a skill name.');
            return;
        }
        const payload = {
            action: "add",
            data: { skill: skillInput }
        };
         try {
            await fetch(SKILLS_API, { method: 'POST', body: JSON.stringify(payload) });
            clearInputs(['skl-add-skill']);
            getSkillsPreview();
        } catch (error) {
            console.error('Error adding skill:', error);
            alert('Error adding skill. Check console.');
        }
    };

    // --- Button: Remove (Dequeue by Index, default 0) ---
document.getElementById('skl-del-btn').onclick = async () => {
    const indexInput = document.getElementById('skl-del-index');
    let indexToDelete = parseInt(indexInput.value);

    // If input is empty or not a valid number, default to 0
    if (isNaN(indexToDelete) || indexToDelete < 0) {
        indexToDelete = 0;
    }

    const payload = {
        action: "remove",
        data: { index: indexToDelete }
    };

    try {
        await fetch(SKILLS_API, { method: 'POST', body: JSON.stringify(payload) });
        clearInputs(['skl-del-index']); // Clear the input after use
        getSkillsPreview();
    } catch (error) { console.error('Error deleting skill:', error); alert('Error deleting skill.'); }
};


    // == 4. ACHIEVEMENTS SCRIPTING


    // --- Render Achievements ---
    function renderAchievementsPreview(dataArray) {
        const previewDiv = document.getElementById('acv-preview-area');
        previewDiv.innerHTML = '';
        if (!dataArray || dataArray.length === 0) {
            previewDiv.innerHTML = "<p class='placeholder'>No achievements pushed.</p>";
            return;
        }
        dataArray.forEach((item, index) => {
            // Note: Stack preview shows newest (index 0) first
            const content = `<strong>${item.description}</strong>`;
             previewDiv.appendChild(createPreviewCard(index, content));
        });
    }

    // --- Get Achievements ---
    async function getAchievementsPreview() {
         try {
            const payload = { action: "preview" };
            const response = await fetch(ACHIEVEMENTS_API, { method: 'POST', body: JSON.stringify(payload) });
            if (!response.ok) throw new Error(`HTTP error! status: ${response.status}`);
            const data = await response.json();
            renderAchievementsPreview(data);
        } catch (error) {
            console.error('Error fetching achievements:', error);
            document.getElementById('acv-preview-area').innerHTML = '<p class="placeholder error">Error loading data.</p>';
        }
    }

    // --- Button: Refresh ---
    document.getElementById('acv-preview').onclick = getAchievementsPreview;

    // --- Button: Add (Push) ---
    document.getElementById('acv-add-btn').onclick = async () => {
         const descInput = document.getElementById('acv-add-desc').value;
         if (!descInput) {
            alert('Please enter an achievement description.');
            return;
        }
        const payload = {
            action: "add",
            data: { description: descInput }
        };
        try {
            await fetch(ACHIEVEMENTS_API, { method: 'POST', body: JSON.stringify(payload) });
            clearInputs(['acv-add-desc']);
            getAchievementsPreview();
        } catch (error) {
            console.error('Error adding achievement:', error);
            alert('Error adding achievement. Check console.');
        }
    };

   // --- Button: Remove (Pop by Index, default 0) ---
document.getElementById('acv-del-btn').onclick = async () => {
    const indexInput = document.getElementById('acv-del-index');
    let indexToDelete = parseInt(indexInput.value);

    // If input is empty or not a valid number, default to 0
    if (isNaN(indexToDelete) || indexToDelete < 0) {
        indexToDelete = 0;
    }

    const payload = {
        action: "remove",
        data: { index: indexToDelete }
    };

     try {
        await fetch(ACHIEVEMENTS_API, { method: 'POST', body: JSON.stringify(payload) });
        clearInputs(['acv-del-index']); // Clear the input after use
        getAchievementsPreview();
    } catch (error) { console.error('Error deleting achievement:', error); alert('Error deleting achievement.'); }
};


    // == 5. ADDITIONAL DETAILS SCRIPTING


     // --- Render Additional ---
    function renderAdditionalPreview(dataArray) {
        const previewDiv = document.getElementById('add-preview-area');
        previewDiv.innerHTML = '';
        if (!dataArray || dataArray.length === 0) {
            previewDiv.innerHTML = "<p class='placeholder'>No additional details added.</p>";
            return;
        }
        dataArray.forEach((item, index) => {
            const content = `<strong>${item.detail}</strong>`;
            previewDiv.appendChild(createPreviewCard(index, content));
        });
    }

    // --- Get Additional ---
    async function getAdditionalPreview() {
         try {
            const payload = { action: "preview" };
            const response = await fetch(ADDITIONAL_API, { method: 'POST', body: JSON.stringify(payload) });
            if (!response.ok) throw new Error(`HTTP error! status: ${response.status}`);
            const data = await response.json();
            renderAdditionalPreview(data);
        } catch (error) {
             console.error('Error fetching additional details:', error);
             document.getElementById('add-preview-area').innerHTML = '<p class="placeholder error">Error loading data.</p>';
        }
    }

    // --- Button: Refresh ---
    document.getElementById('add-preview').onclick = getAdditionalPreview;

    // --- Button: Add ---
    document.getElementById('add-add-btn').onclick = async () => {
        const indexInput = document.getElementById('add-add-index');
        const payload = {
            action: "add",
            data: {
                detail: document.getElementById('add-add-detail').value || 'New Detail',
                index: parseInt(indexInput.value) >= 0 ? parseInt(indexInput.value) : 999
            }
        };
        try {
            await fetch(ADDITIONAL_API, { method: 'POST', body: JSON.stringify(payload) });
            clearInputs(['add-add-detail', 'add-add-index']);
            getAdditionalPreview();
        } catch (error) {
            console.error('Error adding detail:', error);
            alert('Error adding detail. Check console.');
        }
    };

    // --- Button: Remove ---
    document.getElementById('add-del-btn').onclick = async () => {
        const indexInput = document.getElementById('add-del-index');
        const payload = {
            action: "remove",
            data: { index: parseInt(indexInput.value) }
        };
        if (isNaN(payload.data.index) || payload.data.index < 0) {
            alert("Please enter a valid index to delete.");
            return;
        }
        try {
            await fetch(ADDITIONAL_API, { method: 'POST', body: JSON.stringify(payload) });
            clearInputs(['add-del-index']);
            getAdditionalPreview();
        } catch (error) {
             console.error('Error deleting detail:', error);
            alert('Error deleting detail. Check console.');
        }
    };


    // == 6. JOB APPLICATION CYCLE SCRIPTING


    // --- Render Job Cycle ---
    function renderJobCyclePreview(dataArray) {
        const previewDiv = document.getElementById('job-preview-area');
        previewDiv.innerHTML = '';
        if (!dataArray || dataArray.length === 0) {
            previewDiv.innerHTML = "<p class='placeholder'>No job applications added.</p>";
            return;
        }
        dataArray.forEach((item, index) => {
             const content = `<strong>${item.company}</strong>
                             <span>${item.role}</span>
                             <span>Status: ${item.status}</span>`;
            previewDiv.appendChild(createPreviewCard(index, content));
        });
    }

    // --- Get Job Cycle ---
    async function getJobCyclePreview() {
        try {
            const payload = { action: "preview" };
            const response = await fetch(JOB_CYCLE_API, { method: 'POST', body: JSON.stringify(payload) });
            if (!response.ok) throw new Error(`HTTP error! status: ${response.status}`);
            const data = await response.json();
            renderJobCyclePreview(data);
        } catch (error) {
            console.error('Error fetching job cycle:', error);
            document.getElementById('job-preview-area').innerHTML = '<p class="placeholder error">Error loading data.</p>';
        }
    }

    // --- Button: Refresh ---
    document.getElementById('job-preview').onclick = getJobCyclePreview;

    // --- Button: Add ---
    document.getElementById('job-add-btn').onclick = async () => {
         const indexInput = document.getElementById('job-add-index');
        const payload = {
            action: "add",
            data: {
                company: document.getElementById('job-add-company').value || 'Company',
                role: document.getElementById('job-add-role').value || 'Role',
                status: document.getElementById('job-add-status').value || 'Status',
                index: parseInt(indexInput.value) >= 0 ? parseInt(indexInput.value) : 999
            }
        };
         try {
            await fetch(JOB_CYCLE_API, { method: 'POST', body: JSON.stringify(payload) });
            clearInputs(['job-add-company', 'job-add-role', 'job-add-status', 'job-add-index']);
            getJobCyclePreview();
        } catch (error) {
            console.error('Error adding job:', error);
            alert('Error adding job. Check console.');
        }
    };

    // --- Button: Update Status ---
    document.getElementById('job-upd-btn').onclick = async () => {
        const indexInput = document.getElementById('job-upd-index');
        const payload = {
            action: "update",
            data: {
                index: parseInt(indexInput.value),
                status: document.getElementById('job-upd-status').value || 'Updated Status'
            }
        };
        if (isNaN(payload.data.index) || payload.data.index < 0) {
            alert("Please enter a valid index to update.");
            return;
        }
         try {
            await fetch(JOB_CYCLE_API, { method: 'POST', body: JSON.stringify(payload) });
            clearInputs(['job-upd-index', 'job-upd-status']);
            getJobCyclePreview();
        } catch (error) {
            console.error('Error updating job status:', error);
            alert('Error updating job status. Check console.');
        }
    };

    // --- Button: Remove ---
    document.getElementById('job-del-btn').onclick = async () => {
        const indexInput = document.getElementById('job-del-index');
        const payload = {
            action: "remove",
            data: { index: parseInt(indexInput.value) }
        };
        if (isNaN(payload.data.index) || payload.data.index < 0) {
            alert("Please enter a valid index to delete.");
            return;
        }
         try {
            await fetch(JOB_CYCLE_API, { method: 'POST', body: JSON.stringify(payload) });
            clearInputs(['job-del-index']);
            getJobCyclePreview();
        } catch (error) {
            console.error('Error deleting job:', error);
            alert('Error deleting job. Check console.');
        }
    };


    // == INITIAL PAGE LOAD

    getPersonalPreview();
    getEducationPreview();
    getSkillsPreview();
    getAchievementsPreview();
    getAdditionalPreview();
    getJobCyclePreview();

});