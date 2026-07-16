# Bug report user Simulink  Example cannot show window correctly. 

import os
import json
import sys
import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox

class JSONConfigGUI:
	def __init__(self, root):
		self.root = root
		self.root.title("JSON Config Editor")
		self.root.geometry("450x600")  # Set the default width to 450 pixels
		self.root.bind('<Control-s>', self.save_json)  # Bind Ctrl+S to save_json method

		self.config_frame = tk.Frame(self.root)
		self.config_frame.pack(pady=20, fill=tk.BOTH, expand=True)

		self.load_button = tk.Button(self.root, text="Load JSON", command=self.load_json)
		self.load_button.pack(side=tk.LEFT, padx=10)

		self.save_button = tk.Button(self.root, text="Save JSON", command=self.save_json)
		self.save_button.pack(side=tk.LEFT, padx=10)

		self.exit_button = tk.Button(self.root, text="Exit", command=self.on_exit)
		self.exit_button.pack(side=tk.LEFT, padx=10)

		self.checkboxes = {}
		self.descriptions = {}

		# Create a canvas and a scrollbar for the config frame
		self.canvas = tk.Canvas(self.config_frame)
		self.scrollbar = tk.Scrollbar(self.config_frame, command=self.canvas.yview)
		self.scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
		self.canvas.configure(yscrollcommand=self.scrollbar.set)
		self.canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

		# Create a frame inside the canvas to hold the checkboxes and descriptions
		self.inner_frame = tk.Frame(self.canvas)
		self.canvas.create_window((0, 0), window=self.inner_frame, anchor='nw')

		self.inner_frame.bind("<Configure>", lambda event: self.canvas.configure(scrollregion=self.canvas.bbox("all")))

		# this variable is to save json file path
		if len(sys.argv) < 2:
			print("Usage: python script.py <config_file.json>")
			self.file_path = {}
			self.gmp_source_dic_file = {}	
		else:
			self.file_path = sys.argv[1]
			print(sys.argv[1])
			self.gmp_source_dic_file = {}
			self.update_json()
		

	def update_json(self):
		if self.file_path:
			with open(self.file_path, 'r') as file:
				data = json.load(file)
	   
			#self.file_path = file_path

			# Clear the inner frame
			for widget in self.inner_frame.winfo_children():
				widget.destroy()

			# Load descriptions from gmp_source_dic_file
			gmp_source_dic_file_name = data.get("gmp_source_dic_file")

			# Get Environment variables GMP_PRO_LOCATION
			gmp_location_dir = os.getenv('GMP_PRO_LOCATION')
			if not gmp_location_dir:
				print("Environment variable GMP_PRO_LOCATION is not set.")
				sys.exit(1)

			gmp_source_dic_file = gmp_source_dic_file = os.path.join(gmp_location_dir, 'tools', 'facilities_generator', 'json', gmp_source_dic_file_name)
			if gmp_source_dic_file_name:
				self.load_descriptions(gmp_source_dic_file)

			# save source dictionary
			self.gmp_source_dic_file = gmp_source_dic_file_name

			# Create checkboxes for each config item
			current_tag = None
			for key, value in data.items():
				if key != "gmp_source_dic_file":
					item = next((item for item in self.descriptions if item['name'] == key), None)
					description = item['description'] if item and 'description' in item else ""
					tag = item['tag'] if item and 'tag' in item else ""

					if tag != current_tag:
						if current_tag is not None:
							tk.Label(self.inner_frame, text=" ").pack(side=tk.TOP)  # Empty space between groups
						label = tk.Label(self.inner_frame, text=tag, font=('Helvetica', 16, 'bold'))
						label.pack(side=tk.TOP)
						current_tag = tag

					checkbox_var = tk.BooleanVar(value=value)
					cb = tk.Checkbutton(self.inner_frame, text=key, variable=checkbox_var)
					cb.pack(side=tk.TOP, anchor='w', fill=tk.X, expand=True)
					self.checkboxes[key] = checkbox_var

					# Display description if it exists
					if description:
						#label = tk.Label(self.inner_frame, text=description, wraplength=self.root.winfo_width())
						label = tk.Label(self.inner_frame, text=description, wraplength=600)
						label.pack(side=tk.TOP, anchor='w', fill=tk.X, expand=True)

	def load_json(self):
		file_path = filedialog.askopenfilename(title="Select JSON file", filetypes=[("JSON files", "*.json")])
		if file_path:
			self.file_path = file_path

		self.update_json()

	def load_descriptions(self, file_path):
		try:
			with open(file_path, 'r') as file:
				descriptions = json.load(file)
				self.descriptions = descriptions
		except FileNotFoundError:
			messagebox.showerror("Error", "Description file not found.")

	def save_json(self, event=None):
		if self.file_path:
			# no file is loaded
			new_config = {key: var.get() for key, var in self.checkboxes.items()}
			new_config["gmp_source_dic_file"] = self.gmp_source_dic_file
			#file_path = filedialog.asksaveasfilename(title="Save JSON file", filetypes=[("JSON files", "*.json")])
			if self.file_path:
				with open(self.file_path, 'w') as file:
					json.dump(new_config, file, indent=4)
				messagebox.showinfo("Success", "JSON file saved successfully.")

	def on_exit(self):
		if self.file_path:
			if messagebox.askokcancel("Exit", "Do you want to save the changes before exiting?"):
				self.save_json()
		self.root.destroy()

def main():
	root = tk.Tk()
	app = JSONConfigGUI(root)
	root.mainloop()

if __name__ == "__main__":
	main()