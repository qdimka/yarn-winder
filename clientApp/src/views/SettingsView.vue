<!-- https://lightvue.org/vue-components/input -->

<script lang="ts">
import LvInput from 'lightvue/input';
import LvButton from 'lightvue/button';
import {useSettingsStore} from "@/stores/settings";
import {computed} from "vue";
import {storeToRefs} from "pinia";

export default {
  setup() {
    const settings = useSettingsStore();

    const {stepsPerRevolution, gearRatio} = storeToRefs(settings);

    return {
      stepsPerRevolution: stepsPerRevolution,
      gearRatio: gearRatio,
      settings
    }
  },
  methods: {
    async getData() {
      const result = await fetch("/configuration", {
        method: "GET",
        headers: {
          "Content-Type": "application/json",
        },
      })
      const response = await result.json();

      this.settings.updateSettings(response as any);
    },
    async save() {
      await fetch("/configuration", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({
          stepsPerRevolution: this.stepsPerRevolution,
          gearRatio: this.gearRatio
        })
      });
    }
  },
  components: {
    LvInput,
    LvButton
  },
  created() {
    this.getData();
  }
};
</script>

<template>
  <div class="settings">
    <div class="content">
      <div class="settings-input">
        <lv-input type="number" v-model="stepsPerRevolution" label="Количество шагов для полного оборота" placeholder="Введите целое число" :bottom-bar="true"/>
      </div>
      <div class="settings-input">
        <lv-input type="number" v-model="gearRatio" label="Передаточное число" placeholder="Введите целое число" :bottom-bar="true"/>
      </div>
    </div>
    <lv-button @click="save" class="save-btn" label="Сохранить" type="button" size="l" />
  </div>
</template>

<style scoped>
  .settings > .content {
    display: flex;
    flex-direction: column;
    row-gap: 24px;
  }

  .settings > .save-btn {
    margin-top: 32px;
    width: 100%;
  }
</style>
