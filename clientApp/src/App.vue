<script setup lang="ts">
import { RouterLink, RouterView } from 'vue-router'
</script>

<template>
  <div class="container">
    <div class="nav-container">
      <nav>
        <RouterLink to="/">Запуск</RouterLink>
        <RouterLink to="/settings">Настройки</RouterLink>
      </nav>
    </div>
    <div class="body-container">
      <RouterView />
    </div>
  </div>
</template>

<style scoped>

nav a.router-link-exact-active {
  color: var(--color-text);
  border-bottom: 1px solid var(--color-border);
}

nav a.router-link-exact-active:hover {
  background-color: transparent;
}

nav a {
  display: inline-block;
  padding: 0 1rem;
}

.container {
  position: relative;
  max-width: 1024px;
}

.container .nav-container {
  top: 0px;
  position: sticky;
}

.container > .body-container {
  margin-top: 32px;
}
</style>
