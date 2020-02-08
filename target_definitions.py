from pathlib import Path
from typing import List

from cmake_generator import PythonTarget, Target

# ----------------------------------------------------------------
def get_target_definitions() -> List[ Target ] :
    shake_python = PythonTarget(
        name = 'pyshake',
        src_dir_path = ( Path( __file__ ).resolve().parent / 'src/' ).as_posix(),
        dependencies = [
            'glm',
            'pybind11',
            'shake_content',
            'shake_core',
            'shake_ecs',
            'shake_graphics',
            'shake_hid',
            'shake_io',
            'shake_main'
        ]
    )
    return [ shake_python ]
