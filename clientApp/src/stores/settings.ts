import { ref, computed } from 'vue'
import { defineStore } from 'pinia'


export const useSettingsStore = defineStore('settings', () => {
    const stepsPerRevolution = ref(0);
    const gearRatio = ref(0);

    function updateSettings(settings: {stepsPerRevolution: number, gearRatio: number}) {
        stepsPerRevolution.value = settings.stepsPerRevolution;
        gearRatio.value = settings.gearRatio;
    }

    return {
        stepsPerRevolution,
        gearRatio,
        updateSettings
    }
})