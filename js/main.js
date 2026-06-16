/* ===== TYPING EFFECT ===== */
const words = [
  "Full Stack Developer",
  "Creative UI Designer",
  "Frontend Developer",
  "Java Programmer"
];

let i = 0, j = 0, isDeleting = false;

function type() {
  const word = words[i];
  const el = document.getElementById("typing");
  if (!el) return;

  el.textContent = word.substring(0, isDeleting ? j-- : j++);

  if (!isDeleting && j > word.length) {
    isDeleting = true;
    setTimeout(type, 1100);
    return;
  }

  if (isDeleting && j === 0) {
    isDeleting = false;
    i = (i + 1) % words.length;
  }

  setTimeout(type, isDeleting ? 55 : 110);
}

type();


/* ===== SKILL BAR ANIMATION ON SCROLL ===== */
const fills = document.querySelectorAll(".fill");

const observer = new IntersectionObserver((entries) => {
  entries.forEach(entry => {
    if (entry.isIntersecting) {
      const el = entry.target;
      el.style.width = el.dataset.width;
      observer.unobserve(el);
    }
  });
}, { threshold: 0.3 });

fills.forEach(fill => {
  const target = fill.style.width;
  fill.dataset.width = target;
  fill.style.width = "0%";
  observer.observe(fill);
});


/* ===== CONTACT FORM SUBMIT ===== */
const form = document.querySelector("#contact form");
if (form) {
  form.addEventListener("submit", function (e) {
    e.preventDefault();
    const btn = form.querySelector("button");
    btn.textContent = "Message Sent ✓";
    btn.style.background = "#10b981";
    btn.style.color = "white";
    setTimeout(() => {
      btn.textContent = "Send Message";
      btn.style.background = "";
      btn.style.color = "";
      form.reset();
    }, 3000);
  });
}


/* ===== ACTIVE NAV HIGHLIGHT ON SCROLL ===== */
const sections = document.querySelectorAll("section[id]");
const navLinks = document.querySelectorAll("nav ul li a");

window.addEventListener("scroll", () => {
  let current = "";
  sections.forEach(sec => {
    if (window.scrollY >= sec.offsetTop - 80) {
      current = sec.getAttribute("id");
    }
  });
  navLinks.forEach(link => {
    link.style.color = "";
    if (link.getAttribute("href") === `#${current}`) {
      link.style.color = "cyan";
    }
  });
});
